```cpp
#include <3ds.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

long long mod_pow(long long base, long long exp, long long mod)
{
    long long result = 1;
    base %= mod;

    while (exp > 0)
    {
        if (exp & 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp >>= 1;
    }

    return result;
}

vector<int> texto_a_numeros(string text)
{
    vector<int> out;

    for (char c : text)
    {
        if (c == ' ')
            out.push_back(0);
        else if (isalpha(c))
            out.push_back(tolower(c) - 'a' + 1);
    }

    return out;
}

string numeros_a_texto(vector<int> nums)
{
    string out;

    for (int n : nums)
    {
        if (n == 0) out += ' ';
        else out += char('a' + n - 1);
    }

    return out;
}

int main()
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    long long n = 3233;
    long long e = 17;
    long long d = 2753;

    cout << "RSA 3DS SIMPLE\n";
    cout << "n=" << n << " e=" << e << "\n\n";

    string text;
    cout << "Texto: ";
    getline(cin, text);

    vector<int> nums = texto_a_numeros(text);

    cout << "\nCifrado:\n";

    vector<long long> enc;

    for (int v : nums)
    {
        long long c = mod_pow(v, e, n);
        enc.push_back(c);
        cout << c << " ";
    }

    cout << "\n\nDescifrado:\n";

    vector<int> dec;

    for (long long c : enc)
        dec.push_back(mod_pow(c, d, n));

    cout << numeros_a_texto(dec) << "\n";

    cout << "\nPulsa START para salir";

    while (aptMainLoop())
    {
        hidScanInput();
        if (hidKeysDown() & KEY_START) break;
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
```
