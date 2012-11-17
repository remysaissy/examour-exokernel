
//#include "../include/api/fpage.h"

#include "../include/api/kernelinterface.h"
#include <stdio.h>

int	test_bitmask_t();

int main()
{
	if (test_bitmask_t())
	{
		printf("bitmask is ok\n");
	}
	return (0);
}




/* Test for bitmask:
 * return 1 if it's ok, 0 if there is a mistake and 
 * -1 if there is an extern error (eg: Unable to allocate memory)
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream.>

#include "../include/bitmask.h"

#define WRITE	1
#define READ	2
#define EXEC	3

using namespace std;

int	test_bitmask_t()
{
	bitmask_t i;

	i = 0;
	//cout << i.is_set(WRITE) << endl;
	//i += WRITE;
	//cout << i.is_set(WRITE) << endl;

	//if (i == )
	//{
	//	return (0);
	//}

	//bitmask_add(i, READ);
	//if ((i->value & ((1UL << READ) + (1UL <<WRITE))) == 0)
	//{
	//	return (0);
	//}
	//bitmask_sub(i, READ);
	//if ((i->value & (1UL <<WRITE)) == 0)
	//{
	//	return (0);
	//}

	return (1);
}