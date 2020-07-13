#include <iostream>
#include <string>
#include <cassert>

using namespace std;

using byte_t = unsigned char;

char toHex_AL(const byte_t b) noexcept
{
    assert(b <= 0x0F && b >= 0x00); 
    const char c[]
    {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };

    return c[b & 0x0F];
}

string toHex(const byte_t b)
{
    return {toHex_AL(b >> 4), toHex_AL(b & 0x0F)};
}

string toHex(const int v)
{
    string h;
    h += toHex(static_cast<byte_t>(v >> 24));
    h += toHex(static_cast<byte_t>(v >> 16));
    h += toHex(static_cast<byte_t>(v >> 8));
    h += toHex(static_cast<byte_t>(v & 0xFF));

    return h;
}

int main(void)
{
    cout << toHex(4) << endl;        // 0000004
    cout << toHex(11) << endl;       // 000000B 
    cout << toHex(194) << endl;      // 00000CB
    cout << toHex(54684123) << endl; // 34269DB

    return 0;
}