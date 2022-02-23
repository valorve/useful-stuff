#pragma once
#include "bits.hpp"
#include <cstddef>
#include <string>

#ifdef _DEBUG
#define str(x) std::string(x)
#define str_c(x) (x)
#define number(x) (x)
#else

namespace obfuscation {
    static constexpr uint32_t xs32_from_seed(uint32_t seed) {
        seed ^= seed << 13;
        seed ^= seed >> 17;
        seed ^= seed << 15;
        return seed;
    }

    static __forceinline bits64_t hash_bits(bits64_t x, bits64_t key)
    {
        x._xor(bits64_t(948274649985346773LLU)._xor(key));
        x._xor(bits64_t(x).shift_left(13));
        x._xor(bits64_t(x).shift_right(7));
        x._xor(bits64_t(x).shift_left(17));
        return x;
    }

    static constexpr uint64_t hash_u64(uint64_t x, uint64_t key)
    {
        x ^= 948274649985346773LLU ^ key;
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        return x;
    }

    namespace numbers {
        class c_hidden_number {
        private:
            mutable bits32_t m_key = 0;
            mutable uint32_t m_num = 0;
            mutable bool m_decrypted = false;
        public:
            constexpr c_hidden_number(uint32_t num, uint32_t key) {
                m_key = xs32_from_seed(key);
                m_num = num ^ m_key.get();
            }
            __forceinline operator uint32_t() const {
                if (!m_decrypted) {
                    m_num = bits32_t(m_num)._xor(m_key);
                    m_decrypted = true;
                }

                return m_num;
            }
        };

        template <uint32_t num, uint32_t seed>
        __forceinline uint32_t obfuscate() {
            static constexpr auto x = c_hidden_number(num, seed + __TIME__[0] - '0'
                + __TIME__[1] - '0' + __TIME__[3] - '0' + __TIME__[4] - '0'
                + __TIME__[6] - '0' + __TIME__[7] - '0');

            return x;
        }
    }

    namespace strings {
        // TODO: make it better using C++20 features
        template<size_t m_len>
        class c_hidden_string {
        protected:
            mutable uint8_t m_str[m_len];
            mutable bool m_decrypted;
            bits64_t m_key;
        public:
            constexpr c_hidden_string(const char(&str)[m_len], uint64_t key) : m_decrypted(false), m_key(key) {
                for (size_t i = 0; i < m_len; ++i)
                    m_str[i] = str[i] ^ (uint8_t)hash_u64(i, m_key.get());
            }
            operator std::string() const {
                // we won't decrypt it on every call, so lets decrypt it once
                if (!m_decrypted) {
                    // decrypt using our own class bit_vector
                    // so it will be very shitty in IDA
                    for (size_t i = 0; i < m_len; ++i)
                        m_str[i] = bits8_t(m_str[i])._xor((uint8_t)hash_bits(i, m_key)).get();

                    m_decrypted = true;
                }
                return { m_str, m_str + m_len - 1 };
            }
        };

        template<typename type_t, std::size_t n>
        __forceinline constexpr std::size_t calc_size(const type_t(&)[n]) { return n; }

        template <size_t len, uint32_t key>
        __forceinline std::string obfuscate(const char(&str)[len]) {
            static constexpr const obfuscation::strings::c_hidden_string hidden_str(str, key);
            return hidden_str;
        }
    }
}

#define number(n) obfuscation::numbers::obfuscate<n, __LINE__ * __COUNTER__>()

// TODO: make it using template forceinlined function, like numbers
#define str(s) ([]() -> std::string \
{ \
	static constexpr const obfuscation::strings::c_hidden_string hidden_str { s, __LINE__ *__COUNTER__ }; \
	return hidden_str; \
})()

#define str_c(s) str(s).c_str()

#endif