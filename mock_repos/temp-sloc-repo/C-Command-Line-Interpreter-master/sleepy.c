/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @author: David Lei, Student ID: 26029391
 * @since: 1/9/2016
 * @modified: 2/9/2016
 * @params: None
 *
 * Description: Endless loop program to be killed :(
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 // ./sleepy_nostop charmander bulbasaur pikachu squirtle magikarp
#include <unistd.h>
#include <stdio.h>

int main()

{

	int argc = 7;
	char *argv[7];
	argv[0] = "Pikachu";
	argv[1] = "Magikarp";
	argv[2] = "Mudkip";
	argv[3] = "Quagsire";
	argv[4] = "Squirtle";
	argv[5] = "Charmander";
	argv[6] = "Bulbasaur";

	int i = 1;

	int count = 1;
	while(1)
	{
		if (i >= argc)
		{
			i = (i % argc) + 1; 
		}
		printf("%d\n", count);

		printf("%s is sleeping..\n", argv[i]);
		sleep(1);
		printf("..zzzzzZZZZZZZZZZ\n");
		sleep(1);
		printf("%s woke up!!\n", argv[i]);
		sleep(1);
		printf("%s went back to sleep\n", argv[i]);

		i ++;
		count ++;

	}	
	return 0;
}
