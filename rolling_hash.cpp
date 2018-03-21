/*
 * @author: Mohammad Zeineldeen
 * Rolling Hash
*/

const int64_t mod = 1e9+7;
const int64_t p = 17;

struct Hasher {
    std::vector<int64_t> prime_power;
    std::vector<int64_t> prime_inv;
    std::vector<int64_t> prefix_hash;
    std::vector<int64_t> suffix_hash;
    std::string s;

    int64_t mod_pow(int64_t a, int64_t b) {
        int64_t res = 1;
        while (b) {
            if (b & 1) {
                res = (res * a) % mod;
            }
            b >>= 1;
            a = (a * a) % mod;
        }
        return res;
    }

    int64_t mod_inv(int64_t a) {
        return mod_pow(a, mod-2);
    }

    Hasher(std::string str) : s(str) {
        prime_power.resize(s.size());
        prime_inv.resize(s.size());
        prefix_hash.resize(s.size());
        suffix_hash.resize(s.size());
        prime_power[0] = 1;
        prime_inv[0] = 1;
        prefix_hash[0] = s[0];
        for (int i = 1; i < s.size(); ++i) {
            prime_power[i] = (prime_power[i-1] * p) % mod;
            prime_inv[i]   = (prime_inv[i-1] * mod_inv(p)) % mod;
            prefix_hash[i] = (prefix_hash[i-1] + s[i] * prime_power[i]) % mod;
        }
        for (int i = s.size() - 1; i >= 0; --i) {
            suffix_hash[i] = ((i+1 < s.size() ? suffix_hash[i+1] : 0) + s[i] * prime_power[s.size()-i-1]) % mod;
        }
    }

    int64_t get_prefix_hash(int i, int j) {
        if (i > j) return 0;
        return ((prefix_hash[j] - (i > 0 ? prefix_hash[i-1] : 0) + mod) * prime_inv[i]) % mod;
    }

    int64_t get_suffix_hash(int i, int j) {
        if (i > j) return 0;
        return ((suffix_hash[i] - (j+1 < s.size() ? suffix_hash[j+1] : 0) + mod) * prime_inv[s.size()-1-j]) % mod;
    }
};
