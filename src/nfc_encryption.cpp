#include <iostream>
#include <string>
#include <chrono>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>

using namespace CryptoPP;
using namespace std::chrono;

std::string GenerateRandomKey()
{
    AutoSeededRandomPool prng;
    byte key[AES::DEFAULT_KEYLENGTH];
    high_resolution_clock::time_point startTime = high_resolution_clock::now();
    prng.GenerateBlock(key, sizeof(key));
    high_resolution_clock::time_point endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime).count();

    std::string encodedKey;
    StringSource(key, sizeof(key), true,
        new HexEncoder(new StringSink(encodedKey)));

    std::cout << "Key Generation Time: " << duration << " microseconds" << std::endl;

    return encodedKey;
}

std::string Encrypt(const std::string& plainText, const std::string& key)
{
    std::string cipherText;
    CBC_Mode<AES>::Encryption encryption;
    encryption.SetKeyWithIV(reinterpret_cast<const byte*>(key.data()), AES::DEFAULT_KEYLENGTH, (const byte*)"InitializationVector");

    high_resolution_clock::time_point startTime = high_resolution_clock::now();
    StringSource(plainText, true,
        new StreamTransformationFilter(encryption,
            new StringSink(cipherText)));
    high_resolution_clock::time_point endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime).count();

    std::cout << "Encryption Time: " << duration << " microseconds" << std::endl;

    return cipherText;
}

std::string Decrypt(const std::string& cipherText, const std::string& key)
{
    std::string recoveredText;
    CBC_Mode<AES>::Decryption decryption;
    decryption.SetKeyWithIV(reinterpret_cast<const byte*>(key.data()), AES::DEFAULT_KEYLENGTH, (const byte*)"InitializationVector");

    high_resolution_clock::time_point startTime = high_resolution_clock::now();
    StringSource(cipherText, true,
        new StreamTransformationFilter(decryption,
            new StringSink(recoveredText)));
    high_resolution_clock::time_point endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime).count();

    std::cout << "Decryption Time: " << duration << " microseconds" << std::endl;

    return recoveredText;
}

int main()
{
    std::string key = GenerateRandomKey();
    std::cout << "Key Size: " << key.size() << std::endl;

    std::string plainText = "Hello, NFC!";
    std::string cipherText = Encrypt(plainText, key);
    std::cout << "Encrypted Text: " << cipherText << std::endl;

    std::string recoveredText = Decrypt(cipherText, key);
    std::cout << "Decrypted Text: " << recoveredText << std::endl;

    return 0;
}
