#include <iostream>
#include <string>
#include <chrono>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <blesecurity/blesecurity.h>

using namespace CryptoPP;
using namespace std;
using namespace std::chrono;

string GenerateRandomKey()
{
    AutoSeededRandomPool prng;
    byte key[AES::DEFAULT_KEYLENGTH];

    high_resolution_clock::time_point startTime = high_resolution_clock::now();
    prng.GenerateBlock(key, sizeof(key));
    high_resolution_clock::time_point endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime).count();

    string encodedKey;
    StringSource(key, sizeof(key), true,
        new HexEncoder(new StringSink(encodedKey)));

    cout << "Generated Key: " << encodedKey << endl;
    cout << "Key Generation Time: " << duration << " microseconds" << endl;

    return encodedKey;
}

string Encrypt(const string& plainText, const string& key)
{
    string cipherText;
    CBC_Mode<AES>::Encryption encryption;
    encryption.SetKeyWithIV(reinterpret_cast<const byte*>(key.data()), AES::DEFAULT_KEYLENGTH, (const byte*)"InitializationVector");

    high_resolution_clock::time_point startTime = high_resolution_clock::now();
    StringSource(plainText, true,
        new StreamTransformationFilter(encryption,
            new StringSink(cipherText)));
    high_resolution_clock::time_point endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime).count();

    cout << "Encryption Time: " << duration << " microseconds" << endl;

    return cipherText;
}

string Decrypt(const string& cipherText, const string& key)
{
    string recoveredText;
    CBC_Mode<AES>::Decryption decryption;
    decryption.SetKeyWithIV(reinterpret_cast<const byte*>(key.data()), AES::DEFAULT_KEYLENGTH, (const byte*)"InitializationVector");

    high_resolution_clock::time_point startTime = high_resolution_clock::now();
    StringSource(cipherText, true,
        new StreamTransformationFilter(decryption,
            new StringSink(recoveredText)));
    high_resolution_clock::time_point endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime).count();

    cout << "Decryption Time: " << duration << " microseconds" << endl;

    return recoveredText;
}

int main()
{
    string key = GenerateRandomKey();
    cout << "Key Size: " << key.size() << endl;

    string plainText = "Hello, Bluetooth LE!";

    string cipherText = Encrypt(plainText, key);
    cout << "Encrypted Text: " << cipherText << endl;

    string recoveredText = Decrypt(cipherText, key);
    cout << "Decrypted Text: " << recoveredText << endl;

    return 0;
}
