/**
  *@file
  * @author Philip Khristolyubov
  * @version 1.0
  * @date 27.09.2018
  * @brief Первое домашнее задание по курсу "Введение в промышленное программирование и структуры данных"
  * @todo
  */

#include <stdio.h>
#include <math.h>
#include <cassert>

#define BUFSIZE 100                                               ///< difines the size of buffer for user input
#define e 1e-14                                                   ///< if module of value less than e, we consider it to be 0
#define zero_check(inp) ((inp > -e) && (inp < e) ? 0 : 1)         ///< chek if module of value is less than e, end if yes, equate it to 0, else equate it to 1 (used for logical expressions)
#define minus_zero_check(inp) ((inp > -e) && (inp < e) ? 0 : inp) ///< chek if module of value is less than e, end if yes, equate it to 0
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
 * @brief Solves bx+c=0 linear equation
 * @param b[in] 'b' coefficient of equation
 * @param c[in] 'c' coefficient of equation
 * @param x1[out] pointer to the root of equation
 * @return number of found roots
 */
int SolveLinear(double b, double c, double* x1);

/**
 * @brief Solves ax^2+bx+c=0 equation
 * @param a[in] 'a' coefficient of equation
 * @param b[in] 'b' coefficient of equation
 * @param c[in] 'c' coefficient of equation
 * @param x1[out] pointer to the first root of equation
 * @param x2[out] pointer to the second root of equation
 * @return number of found roots
 */
int SolveSqare(double a, double b, double c, double* x1, double* x2);

enum
{COMPLEX_ROOTS = -1, NO_ROOTS, ONE_ROOT, TWO_ROOTS};

int main()
{
    printf("# SqareEqSolver v1.0 (c) Philipp Khristolyubov\n");
    printf("# Enter a, b, c: ");

    double a = static_cast<double>(NAN) , b = static_cast<double>(NAN), c = static_cast<double>(NAN);
    char buf[BUFSIZE];
    while (sscanf(fgets(buf, BUFSIZE, stdin), "%lg %lg %lg", &a, &b, &c) != 3)
        printf("#Please, enter 3 numbers on one line: ");

    double x1 = static_cast<double>(NAN), x2 = static_cast<double>(NAN);
    int nRoots = SolveSqare(a, b, c, &x1, &x2);

    switch (nRoots)
    {
    case COMPLEX_ROOTS: printf("# There are two complex roots\n"); break;
    case NO_ROOTS:  printf("# There are no roots\n"); break;
    case ONE_ROOT:  printf("# There is one root: %lg\n", minus_zero_check(x1)); break;
    case TWO_ROOTS:  printf("# There are two roots: %lg %lg\n", minus_zero_check(x1), minus_zero_check(x2)); break;
    default: printf("# Strange nRoots = %d in SolveSquare (%lg, %lg, %lg)\n", nRoots, a, b, c); break;
    }
    return 0;
}

int SolveLinear(double b, double c, double* x1)
{
    assert(std::isfinite(b)); assert(std::isfinite(c));
    assert((x1 != nullptr));

    if (zero_check(b) == 0)
        return 0;
    else /* if(b != 0) */
    {
        *x1 = -c/b;
        return 1;
    }
}

int SolveSqare(double a, double b, double c, double* x1, double* x2)
{
    assert(std::isfinite(a)); assert(std::isfinite(b)); assert(std::isfinite(c));
    assert((x1 != nullptr)); assert((x2 != nullptr));

    if (zero_check(a) == 0)
        return SolveLinear(b, c, x1);
    else
    {
        double D = b*b - 4*a*c;
        if (D < 0)
            return -1;
        else if (zero_check(D) == 0)
        {
            *x1 = -b/2/a;
            return 1;
        }
        else /* if (D > 0) */
        {
            *x1 = (-b+sqrt(D))/2/a;
            *x2 = (-b-sqrt(D))/2/a;
            return 2;
        }
    }
}
