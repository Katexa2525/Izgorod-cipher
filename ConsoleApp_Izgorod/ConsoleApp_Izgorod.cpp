//ввести ключ и строку и зашифровать
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

// структура для записи подстрок зашифрованной строки
struct arrStr {
  char strS[100];
};

char s[100];
char s1[100];
int key, initL=0;

// прототипы функций
void Encrypt(char* s, int key);
void Decrypt(char* s, int key);
int FindingMultiple(int L, int key);
void FillArrSubStr(char* s, struct arrStr strArray[], int K, int K2, int countWord);

int main()
{
  setlocale(LC_ALL, "Russian");
  printf("Введите ключ: \n");
  scanf("%d", &key);
  printf("Введите строку: \n");
  scanf("%s", &s);

  if (key == 1 || key >= strlen(s))
  {
    printf("Зашифрованная строка: %s \n", s);
    printf("Дешифрованная строка: %s \n", s);
  }
  else
  {
    initL = strlen(s); // длина введенной строки
    int L = FindingMultiple(strlen(s), key); // Нахожу длину строки L, которая будет кратная 2*(key-1)
    // дополняю строку символом '¬', чтобы длина строки была = L
    int i = strlen(s);
    while (L > i)
    {
      s[i] = '¬';
      i++;
    }
    Encrypt(s, key);
    Decrypt(s, key);
  }

  return 0;
}

/// <summary> Шифрование строки </summary>
/// <param name="s">Строка для шифрования</param>
/// <param name="key">Ключ, или кол-во рельс</param>
void Encrypt(char* s, int key)
{
  int i = 0, ii = 0, p = 1, RezN, j;
  while (i < key)
  {
    RezN = key * 2 - p;
    j = i;
    int pr = 0; // признак того, что первый символ был взят
    while (j < strlen(s))
    {
      if (pr == 0)
      {
        s1[ii] = s[j];
        ii++;
        pr++;
      }
      else
      {
        if (i == key - 1) // если самая нижняя часть забора
        {
          s1[ii] = s[j + p - 1];
          j = j + p - 1;
        }
        else
        {
          s1[ii] = s[j + RezN - 1];
          j = j + RezN - 1;
        }
        ii++;

        if (j + p - 1 >= strlen(s))
          break;
        else if (p > 1 && p != key * 2 - 1)
        {
          s1[ii] = s[j + p - 1];
          ii++;
          j = j + p - 1;
        }
      }
      // если след расчет превышает строку, то выход из цикла
      if (j + RezN - 1 >= strlen(s))
        break;
    }
    i++;
    p = p + 2;
  }
  printf("\nЗашифрованная строка: %s \n", s1);
}

/// <summary> Расшифровка строки </summary>
/// <param name="s">Строка</param>
/// <param name="key">Ключ, кол-во рельс</param>
void Decrypt(char* s, int key)
{
  struct arrStr strArray[100];
  char decrS[100];

  int L = strlen(s);
  int K = L / (2 * (key - 1)); // длина первой и последней подстроки
  int K2 = K * 2;
  int countWord = 2 + ((L - K * 2) / K2); // 2 слова (первое и последнее по K символов) + кол-во слов по 2*К символов

  //Заполняю массив структуры подстроками
  FillArrSubStr(s1, strArray, K, K2, countWord);

  int nn = 0; // номер буквы, какую брать
  int dz = 0; // номер нижнего зубца в заборе
  int uz = 0; // номер верхнего зубца в заборе
  // расшифровка
  for (int i = 0; i < L; i++)
  {
    if (i == 0)
    {
      for (int j = 0; j < countWord; j++)
      {
        decrS[nn] = strArray[j].strS[0];
        nn++; 
        if (nn >= initL) break;
      }
      dz++; uz++;
    }
    else if (i % 2 != 0) // если нечетная i, тогда с предпоследнего массива до первого из strArray беру букву с индекса i
    {
      for (int j = countWord-2; j >= 0; j--)
      {
        if (j == 0)
          decrS[nn] = strArray[j].strS[i - (i - uz)];
        else
          decrS[nn] = strArray[j].strS[i];
        nn++;
        if (nn >= initL) break;
      }
      uz++;
    }
    else if (i % 2 == 0) // если нечетная i, тогда со второго массива до последнего из strArray беру букву с индексом i
    {
      for (int j = 1; j < countWord; j++)
      {
        if (j == countWord - 1)
          decrS[nn] = strArray[j].strS[i - (i - dz)];
        else
          decrS[nn] = strArray[j].strS[i];
        nn++;
        if (nn >= initL) break;
      }
      dz++;
    }
    if (nn >= initL) break;
  }
  // вывод расшифровки
  printf("\nРасшифрованная строка: ");
  for (int i = 0; i < nn; i++)
  {
    printf("%c", decrS[i]);
  }
  printf("\n");
}

/// <summary> Нахожу длину строки L, которая будет кратная 2*(key-1) </summary>
/// <param name="L">Длина строки</param>
/// <param name="key">Ключ. Кол-во рельс</param>
/// <returns>Новая длина строки L</returns>
int FindingMultiple(int L, int key)
{
  int zn = 2 * (key - 1);
  while (L % zn != 0)
    L++;
  return L;
}

/// <summary> Заполняю массив структуры подстроками </summary>
void FillArrSubStr(char* s, struct arrStr strArray[], int K, int K2, int countWord)
{
  int j = 0;
  for (int i = 0; i < countWord; i++)
  {
    for (int p=0; j < strlen(s); j++, p++)
    {
      if (((i == 0 || i == countWord - 1) && p >= K) || p >= K2)
        break;
      strArray[i].strS[p] = s[j];
    }
  }
}