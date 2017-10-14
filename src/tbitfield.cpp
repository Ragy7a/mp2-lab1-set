// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen=len;
	MemLen=BitLen/sizeof(TELEM)+1;
	pMem=new TELEM(MemLen)+1;
	for (int i=0; i<BitLen; i++)
	{
		pMem[i]=0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen=bf.BitLen;
	MemLen=bf.MemLen;
	pMem=new TELEM(MemLen)+1;
	for(int i=0; i<BitLen; i++)
	{
		pMem[i]=bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n/sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM temp=1;
	temp=temp<<(n%sizeof(TELEM));
	return temp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	pMem[GetMemIndex(n)]|=GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[GetMemIndex(n)]&=~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return pMem[GetMemIndex(n)]&GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if(MemLen!=bf.MemLen)
	{
		MemLen=bf.MemLen;
		delete[] pMem;
		pMem=new TELEM[MemLen];
	}
	BitLen=bf.BitLen;
	for (int i=0; i<MemLen; i++)
	{
		pMem[i]=bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (bf.BitLen!=BitLen)
		return 0;
	else
		for (int i=0; i<MemLen; i++)
		{
			if(bf.pMem[i]!=this->pMem[i])
				return 0;
		}
		for (int i=BitLen-1; i>BitLen-BitLen%32; i--)
		{
			if (bf.GetBit(i)!=this->GetBit(i))
				return 0;
		}
		return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (bf.BitLen!=BitLen)
		return 1;
	else
		for (int i=0; i<MemLen; i++)
		{
			if(bf.pMem[i]!=this->pMem[i])
				return 1;
		}
		for (int i=BitLen-1; i>BitLen-BitLen%32; i--)
		{
			if (bf.GetBit(i)!=this->GetBit(i))
				return 1;
		}
		return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField temp(BitLen);
	for (int i=0; i<MemLen; i++)
	{
		temp.pMem[i]=pMem[i]|bf.pMem[i];
	}
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField temp(BitLen);
	for (int i=0; i<MemLen; i++)
	{
		temp.pMem[i]=pMem[i]&bf.pMem[i];
	}
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(BitLen);
	for (int i=0; i<MemLen; i++)
	{
		temp.pMem[i]=~pMem[i];
	}
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
int temp;
for (int i=0; i<bf.GetLength(); i++)
{
	istr >> temp;
	if (temp==1)
	{
		bf.SetBit(i);
	}
	else
		bf.ClrBit(i);
}
return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{	for (int i=0; i<bf.GetLength(); i++)
	{
		if (bf.GetBit(i)>0)
			ostr<< 1;
		else
			ostr<< 0;
		return ostr;
	}
}
