#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<Windows.h>
#include <stdint.h>
#define DELTA 0x9e3779b9
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (key[(p&3)^e] ^ z)))


// ÎØÎØÎØ£¬Author by ÃÎÓÎÇ¹ÊÖ
void btea(uint32_t* v, int n, uint32_t const key[4])
{
	uint32_t y, z, sum;
	unsigned p, rounds, e;
	if (n > 1)            /* Coding Part */
	{
		rounds = 6 + 52 / n;
		sum = 0;
		z = v[n - 1];
		do
		{
			sum += DELTA;
			e = (sum >> 2) & 3;
			for (p = 0; p < n - 1; p++)
			{
				y = v[p + 1];
				z = v[p] += MX;
			}
			y = v[0];
			z = v[n - 1] += MX;
		} while (--rounds);
	}
	else if (n < -1)      /* Decoding Part */
	{
		n = -n;
		rounds = 6 + 52 / n;
		sum = rounds * DELTA;
		y = v[0];
		do
		{
			e = (sum >> 2) & 3;
			for (p = n - 1; p > 0; p--)
			{
				z = v[p - 1];
				y = v[p] -= MX;
			}
			z = v[n - 1];
			y = v[0] -= MX;
			sum -= DELTA;
		} while (--rounds);
	}
}
int main()
{
	unsigned int enc[] =
	{
	0xfd9998ba, 0x45f90c51, 0x70473a18, 0x0b889897, 0x8256b64d, 0x32f1ae81, 0x1cfa40d0, 0xf95cc487, 0xf37a2fd3, 0x6365d798
	};
	unsigned int v[2] = { enc[0],enc[1] };
	unsigned int  key[4] = { 1, 2, 3, 4 };
	btea(enc, -(int)(sizeof(enc) / 4), key);
	printf("%s\n", enc);
	printf("decode: %x %x\n", enc[0], enc[1]);
	getchar();
}