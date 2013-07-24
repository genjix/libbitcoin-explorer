#ifndef SX_LOAD_TX_HPP
#define SX_LOAD_TX_HPP

#include <bitcoin/bitcoin.hpp>

using namespace bc;

bool load_tx(transaction_type& tx, const std::string& filename)
{
    std::ostringstream contents;
    if (filename == "-")
    {
        std::istreambuf_iterator<char> first(std::cin);
        std::istreambuf_iterator<char> last;
        contents << std::string(first, last);
    }
    else
    {
        std::ifstream infile(filename, std::ifstream::binary);
        if (!infile)
        {
            std::cerr << "showtx: Bad file." << std::endl;
            return false;
        }
        contents << infile.rdbuf();
    }
    data_chunk raw_tx = decode_hex(contents.str());
    try
    {
        satoshi_load(raw_tx.begin(), raw_tx.end(), tx);
    }
    catch (end_of_stream)
    {
        std::cerr << "showtx: Deserializing transaction failed." << std::endl;
        return false;
    }
    return true;
}

std::string read_stdin()
{
    std::istreambuf_iterator<char> first(std::cin);
    std::istreambuf_iterator<char> last;
    return std::string(first, last);
}

bool read_private_key(elliptic_curve_key& key)
{
    secret_parameter secret = wif_to_secret(read_stdin());
    if (secret == null_hash || !key.set_secret(secret))
    {
        std::cerr << "Invalid private key." << std::endl;
        return false;
    }
    return true;
}

#endif
