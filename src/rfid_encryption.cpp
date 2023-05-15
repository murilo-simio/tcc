#include <iostream>
#include <string>
#include <chrono>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <MFRC522.h>

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
    MFRC522 rfid(10, 9); // pin RST to 10, pin SS to 9

    if (!rfid.PCD_Init()) {
        cout << "Failed to initialize RFID reader" << endl;
        return -1;
    }

    string key = GenerateRandomKey();
    cout << "Key Size: " << key.size() << endl;

    string plainText = "Hello, RFID!";

    // Write plain text to card
    byte block = 0;
    byte buffer[16];
    memset(buffer, 0, sizeof(buffer));
    plainText.copy(reinterpret_cast<char*>(buffer), 16, 0);
    if (rfid.MIFARE_Write(block, buffer, 16) != MFRC522::STATUS_OK) {
        cout << "Failed to write to card" << endl;
        return -1;
    }

    // Read plain text from card
    memset(buffer, 0, sizeof(buffer));
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        if (rfid.MIFARE_Read(block, buffer, nullptr) != MFRC522::STATUS_OK) {
            cout << "Failed to read from card" << endl;
            return -1;
        }
    }

    string receivedText(reinterpret_cast<char*>(buffer), 16);
    cout << "Received Text: " << receivedText << endl;

    string cipherText = Encrypt(plainText, key);
    cout << "Encrypted Text: " << cipherText << endl;

    string recoveredText = Decrypt(cipherText, key);
    cout << "Decrypted Text: " << recoveredText << endl;

    return 0;
}

