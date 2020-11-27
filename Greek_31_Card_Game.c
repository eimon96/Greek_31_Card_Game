#include <stdio.h>
#include <windows.h>
#include <stdbool.h>


int main()
{
	system("Color 0A");
	
				
	//game
	
	home:
	
	printf("\
			//////////////////////////////////////////\n\
			////            WELCOME!              ////\n\
			//////////////////////////////////////////");
	sleep(1);
	printf("\nLets play the Greek 31 card game!!!");
	sleep(1);
	printf("\nYOU against ME!");
	sleep(1);
	
	printf("\n\nPress 'P' to play");
	printf("\nPress 'Q' to quit");
	printf("\nPress 'R' for the rules\t");
	char key = toupper(getche());
	if (key == 'Q')	exit(1);
	if (key == 'R')
	{
		system("cls");
		rules();
		goto home;
	}
	
	//deck array
	int deck[13];
	int c;
	for (c = 0; c < 13; c++ ) {
      deck[c] =  c + 1;
   	}
   	
   	
	
	while (key == 'P'){
		system("cls");
		printf("\nI am the dealer..Lets go.\n\n");
		sleep(1);
		
		printf("\nDrawing cards...");
		sleep(2);
			
		srand((unsigned)time(NULL));
		int rand1 = rand() % 13 + 1;
		int rand2 = rand() % 13 + 1;
		
		int dealer_cards[10];
		printf("\nMy 2nd card is hidden.\n");
		sleep(1);
		printf("\nMy 1st card:\n");
		
		// reveal the smallest card although NOT the ace :P
		if ((rand1 > rand2 && rand2 != 1 ) || (rand1 == 1))
		{
			int temp = rand1;
			rand1 = rand2;
			rand2 = temp;
		}
		dealer_cards[0] = rand1;
		dealer_cards[1] = rand2;
		
		showCards(dealer_cards, 1); 
		sleep(1);
		
		int dealer_size = 2;
		int sumD = 0;
		sumD = Summ(rand1, sumD);
		sumD = Summ(rand2, sumD);
	
		
		int rand3 = rand() % 13 + 1;
		int rand4 = rand() % 13 + 1;
		
		bool bust = false;
		int noob_cards[10];
		noob_cards[0] = rand3;
		noob_cards[1] = rand4;
		printf("\nYour cards:\n");
		sleep(1);
		int noob_size = 2;
		showCards(noob_cards, noob_size);
		
		int sumN = 0;
		
		
		
		
		// ACESFUNC1
		int flagAceN = 0;	// 0 = ace is still 1 - 1 = ace has changed to 11 --- combined with countAces
		int countAces = 0;
		if (CheckAce(rand3) && CheckAce(rand4))
		{
			sumN = Summ(10, sumN);
			countAces = 2;
//			flagAceN = 0;  player can change the other - ask later
		}
		else if (CheckAce(rand3) || CheckAce(rand4))
		{
			countAces = 1;
			printf("Wanna count A as 11?(y/n): ");
			char answerAce = toupper(getche());
			if (answerAce == 'Y') 
			{
				sumN = Summ(10, sumN);
				flagAceN = 1; // ace has changed to 11
			}
				
		}
		sleep(1);
		
		
		
		
		
		
		// ACESFUNC3-DEALER
		int flagAceDD = 0;	// 0 = ace is still 1 - 1 = ace has changed to 11 --- combined with countAces
		int countAcesDD = 0;
		if (CheckAce(rand1) && CheckAce(rand2))
		{
			sumD = Summ(10, sumD);
			countAcesDD = 2;
//			flagAceDD = 0;  dealer can change the other - check later
		}
		else if (CheckAce(rand1) || CheckAce(rand2))
			countAcesDD = 1; // flagAceDD = 0 and check later
		
		
		
		
		
	
		
		
		sumN = Summ(rand3, sumN);
		sumN = Summ(rand4, sumN);
		
		bool N_14 = Check14(sumN);
		if (rand3 == rand4 && rand3 == 2)
		{
			sumN = 14;
			N_14 = 1;
		}
		if (N_14)
		{
			printf("\n\nYou have 14! I must go to 31.\n\n");
			sleep(2);
			goto deal;
		}
		
		
		
		//players turn
		char hit;
		printf("\nSum: %d\n",sumN);
		printf("\nHit or stand (h/s)?: ");
		hit = toupper(getche());
		while (hit == 'H')
		{
			int rr = rand() % 13 + 1;
			noob_size++;
			noob_cards[noob_size-1] = rr;
			printf("\nYour cards:\n");
			showCards(noob_cards, noob_size);
			
			
			
			
			char answerAce;
			int newAce = 0;
			// ACESFUNC2
			if (CheckAce(rr))
			{
				countAces++;
				newAce = 1;
			}
			if (countAces == 1)
			{
				
				printf("Wanna count A as 11?(y/n): ");
				answerAce = toupper(getche());
				if (answerAce == 'Y' && flagAceN == 0) // ace is 1 wanted 11 add 10
				{	
					sumN = Summ(10, sumN);
					flagAceN = 1; // ace has changed to 11
				}
//				if (answerAce == 'Y' && flagAceN == 1)  ace is 11 no action
//				if (answerAce == 'N' && flagAceN == 0)  ace is 1 wanted 1 no action
				if (answerAce == 'N' && flagAceN == 1)  // ace is 11 wanted 1 sub 10
				{	sumN = Summ(-10, sumN);
					flagAceN = 0; // ace is 1 again
				}
			}
			if (countAces > 1)
			{
				if (newAce = 1)
				{
					sumN = Summ(10, sumN);
					newAce = 0;
				}
				printf("Wanna count 1st A as 11?(y/n): ");
				answerAce = toupper(getche());
				if (answerAce == 'Y' && flagAceN == 0)
				{	
					sumN = Summ(10, sumN);
					flagAceN = 1; // ace has changed to 11
				}
				if (answerAce == 'N' && flagAceN == 1)  // ace is 11 wanted 1 sub 10
				{	sumN = Summ(-10, sumN);
					flagAceN = 0; // ace is 1 again
				}
			}
			sleep(1);
		
		
		
		
			
			
			sumN = Summ(rr, sumN);
			
			if (sumN > 31)
			{
				sleep(1);
				printf("\nBUSTED!\n");
				sleep(2);
				bust = true;
				break;
			}
			if (sumN == 31)
			{
				sleep(1);
				printf("\n-31-\n");
				sleep(2);
				printf("\n...\n");
				sleep(1);
				break;
			}
			N_14 = Check14(sumN);
			if (N_14)
			{
				printf("\n\nYou have 14! I must go to 31.\n\n");
				sleep(2);
				goto deal;
			}
			
			printf("\nSum: %d\n",sumN);
			printf("\nHit or stand (h/s): ");
			hit = toupper(getche());
		}
		
		
		
		deal: ;
			
		// dealers turn
		printf("\nMy cards:\n");
		showCards(dealer_cards, dealer_size);
		sleep(1);
		
		bool D_14 = Check14(sumD);
		if ((rand1 == rand2 && rand3 == 2) || (rand1 == 3 && rand2 == 1) || (rand1 == 1 && rand2 == 3))
		{
			sumD = 14;
			D_14 = 1;
		}
		if (D_14)
		{
			if (N_14) 
				printf("\n\nLooks like I have 14 too :P I am the winner!!.\n\n");
			else if (sumN < 31) 
				printf("\n\nLooks like I have 14 and you dont have the sum of 31 (%d).. I am the winner!!.\n\n", sumN);
			else if (sumN == 31) 
				printf("\nReally, now? Okay, fine, you won...\n\n");
			else if (bust)
				printf("\nI WON!\n");
				
			goto end;
		}
		
		
		printf("\nSum: %d\n",sumD);
		sleep(2);
		
		if (N_14) goto loopa;
		
		while (sumD < sumN && !bust)
		{
			loopa: ;
				
			int rr = rand() % 13 + 1;
			dealer_size++;
			dealer_cards[dealer_size-1] = rr;
			printf("\nMy cards: ");
			showCards(dealer_cards, dealer_size);
			sleep(1);
			
			
			
			
			
			
			int newAceDD = 0;
			// ACESFUNC4-DEALER
			if (CheckAce(rr))
			{
				countAcesDD++;
				newAceDD = 1;
			}
			if (countAcesDD == 1)
			{
				if (flagAceDD == 0 && (sumD + 10 <= 31))
				{
					sumD = Summ(10, sumD);
					flagAceDD = 1;
				} 
				if (flagAceDD == 1 && (sumD + rr > 31))
				{
					sumD = Summ(-10, sumD);
					flagAceDD = 0;
				}
				
			}
			if (countAcesDD > 1)
			{
				if (newAceDD = 1)
				{
					sumD = Summ(10, sumD);
					newAceDD = 0;
				}
				
				
				if (flagAceDD == 0 && (sumD + 10 <= 31))
				{
					sumD = Summ(10, sumD);
					flagAceDD = 1;
				} 
				if (flagAceDD == 1 && (sumD + rr > 31))
				{
					sumD = Summ(-10, sumD);
					flagAceDD = 0;
				}

			}
			
			
			
			
			
			
			
			
			sumD = Summ(rr, sumD);
			printf("\nSum: %d\n",sumD);
			sleep(2);
			
			D_14 = Check14(sumD);
			if (D_14)
			{
				if (N_14) 
					printf("\n\nLooks like I have 14 too :P I am the winner!!.\n\n");
				else if (sumN < 31) 
					printf("\n\nLooks like I have 14 and you dont have the sum of 31 (%d).. I am the winner!!.\n\n", sumN);
				else if (sumN == 31) 
					printf("\nReally, now? Okay, fine, you won...\n\n");
				else if (bust)
					printf("\nI WON!\n");
					
				goto end;
			}
			
			if (N_14 && sumD < 31 ) goto loopa;
		}
		
		
		
		// we have a winner
		printf("\nSum of my cards: %d\nSum of your cards: %d", sumD, sumN);
		sleep(1);
		
		if ((sumD >= sumN && sumD <= 31) || bust) printf("\nI WON!\n");
		else printf("\nYou won...lame.\n");
		sleep(1);
		
		
		end:
			
		printf("\nWanna play again?(P/Q): ");
		key = toupper(getche());
		if (key == 'Q')	
		{
			system("cls");
			goto home;
		}
	}
	
	return 0;
}




void showCards(int *array_cards, int siz)
{
	
	// card 'visuals' - no suits => infinite decks
	const char ace[]="\n*************\
				\n* A         *\
		    	\n*           *\
				\n*           *\
				\n*           *\
				\n*     *     *\
				\n*           *\
				\n*           *\
				\n*           *\
				\n*         A *\
				\n*************\n\n";
				
	const char two[]="\n*************\
				\n* 2         *\
		    	\n*           *\
				\n*     *     *\
				\n*           *\
				\n*           *\
				\n*           *\
				\n*     *     *\
				\n*           *\
				\n*         2 *\
				\n*************\n\n";
	
	const char three[]="\n*************\
				\n* 3         *\
		    	\n*           *\
				\n*     *     *\
				\n*           *\
				\n*     *     *\
				\n*           *\
				\n*     *     *\
				\n*           *\
				\n*         3 *\
				\n*************\n\n";
				
	const char four[]="\n*************\
				\n* 4         *\
		   		\n*           *\
				\n*  *     *  *\
				\n*           *\
				\n*           *\
				\n*           *\
				\n*  *     *  *\
				\n*           *\
				\n*         4 *\
				\n*************\n\n";	
	
	const char five[]="\n*************\
				\n* 5         *\
			    \n*           *\
				\n*  *     *  *\
				\n*           *\
				\n*     *     *\
				\n*           *\
				\n*  *     *  *\
				\n*           *\
				\n*         5 *\
				\n*************\n\n";
				
	const char six[]="\n*************\
				\n* 6         *\
			    \n*           *\
				\n*  *     *  *\
				\n*           *\
				\n*  *     *  *\
				\n*           *\
				\n*  *     *  *\
				\n*           *\
				\n*         6 *\
				\n*************\n\n";
				
	const char seven[]="\n*************\
				\n* 7         *\
			    \n*           *\
				\n*  *     *  *\
				\n*     *     *\
				\n*  *     *  *\
				\n*           *\
				\n*  *     *  *\
				\n*           *\
				\n*         7 *\
				\n*************\n\n";
				
	const char eight[]="\n*************\
				\n* 8         *\
			    \n*           *\
				\n*  *     *  *\
				\n*     *     *\
				\n*  *     *  *\
				\n*     *     *\
				\n*  *     *  *\
				\n*           *\
				\n*         8 *\
				\n*************\n\n";
				
	const char nine[]="\n*************\
				\n* 9         *\
			    \n*  *     *  *\
				\n*           *\
				\n*  *     *  *\
				\n*     *     *\
				\n*  *     *  *\
				\n*           *\
				\n*  *     *  *\
				\n*         9 *\
				\n*************\n\n";
				
	const char ten[]="\n*************\
				\n* 10        *\
	   			\n*  *     *  *\
				\n*     *     *\
				\n*  *     *  *\
				\n*           *\
				\n*  *     *  *\
				\n*     *     *\
				\n*  *     *  *\
				\n*        10 *\
				\n*************\n\n";
				
	const char jack[]="\n*************\
				\n* J         *\
	   			\n*           *\
				\n*  J A C K  *\
				\n*    | |    *\
				\n*    | |    *\
				\n*    | |    *\
				\n*           *\
				\n*           *\
				\n*         J *\
				\n*************\n\n";
				
	const char queen[]="\n*************\
				\n* Q         *\
	   			\n*           *\
				\n*  Q U EE N *\
				\n*    / \\    *\
				\n*    / \\    *\
				\n*    / \\    *\
				\n*           *\
				\n*           *\
				\n*         Q *\
				\n*************\n\n";
								
	const char king[]="\n*************\
				\n* K         *\
	   			\n*           *\
				\n*  K I N G  *\
				\n*   / /\\ \\  *\
				\n*  /\\/\\/\\/\\ *\
				\n*  \\      / *\
				\n*   \\    /  *\
				\n*    \\  /   *\
				\n*         K *\
				\n*************\n\n";
				
				
				
	int c;
	for (c = 0; c < siz; c++)
	{
		switch(array_cards[c])
		{
			case(1):
				printf("%s", ace);
				break;
			case(2):
				printf("%s", two);
				break;
			case(3):
				printf("%s", three);
				break;
			case(4):
				printf("%s", four);
				break;
			case(5):
				printf("%s", five);
				break;
			case(6):
				printf("%s", six);
				break;
			case(7):
				printf("%s", seven);
				break;
			case(8):
				printf("%s", eight);
				break;
			case(9):
				printf("%s", nine);
				break;
			case(10):
				printf("%s", ten);
				break;
			case(11):
				printf("%s", jack);
				break;
			case(12):
				printf("%s", queen);
				break;
			case(13):
				printf("%s", king);
				break;
		}
	}
}


void rules()
{
	printf("\n\n\n\
			You aim the sum of 31. If you exceed 31 you got bust.\n\
			If neither the player nor the dealer has 31 then the one with the bigger sum wins.\n\
			If tie, dealer wins.\n\
			In case of 14, the opponent must get 31 to win, otherwise the one with the 14 wins.\n\
			A pair of Twos is worth as 14 although only if it's not combined with other cards\n\
			If tie, dealer wins.\n\
			Aces count as 1 or 11 at the players choice.However a player who has more than one Ace\n\
			must count them as 11 except one of them.\n\n\
			Read more about the rules at  https://www.pagat.com/banking/31.html \n\n");
	system("pause");
	system("cls");
}


int Summ(int draw, int sum)
{
	if (draw == 11 || draw == 12 || draw == 13) sum += 10;
	else sum += draw;
	
	return (sum);
}


int Check14(int s)
{	
	if (s == 14) 	return (1);
	else 			return (0);
}


int CheckAce(int draw)
{
	if (draw == 1) 	return (1);
	else			return (0);
}





// eimon96 11/2020 <<3







