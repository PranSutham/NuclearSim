// Team 9: Roshen Abdullah, Jake Gorman, Pran Sutham

// Nuclear Power Plant Simulator: This game gives the player the exciting chance to run a nuclear power plant! The challenge is to survive for as many
// years as possible given random unexpected costs that may arise along the way, changes in government that will directly affect your expenses,
// consequences of taking the cheaper but dodgy way out and more. The game also ends should the player be sent to prison for tax fraud. As the game goes on,
// the player will discover that they must make some unethical/shady decisions and not play by the rules all the time, lest they face bankrupty!

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void randomEvent(int[], double[]);

void Taxes(int[], double[]);
void Wages(int[], double[]);
void WasteManagement(int[], double[]);
void OperatingCosts(int[], double[]);

void PoliticalContributions(int[], double[]);
void Loans(int[], double[]);

void PRDisaster(int[], double[], double, char[]);

int promptUser(char[]);
int loan1Option(int[], double[]);
int loan2Option(int[], double[]);

int main()
{
	srand(time(0));
	
	int userChoice1 = 1;
	while (userChoice1 == 1) // all the code for Nuclear Power Plant Simulator goes in this if statement
	{
		// NOTE: The most impactful change you can make if you wish to make the game more difficult is to change the increment amount
		// of Catastrophe in the randomEvent function!
		// rand() increments for this version (experiment as desired): +10 Catastrophe, +2 Good Fortune, +3 Wild Card
		printf("\n-----------------------------------------------------------------------------------\n\n");
		printf("Welcome to Nuclear Power Plant Simulator! You are the proud owner of the Springfield Nuclear Power Plant.");
		printf("\nDue to your father's unexpected retirement, you have been give a small loan of a million dollars");
		printf(" as well as complete ownership of the plant.\nLet's see how well your Wharton degree prepares");
		printf(" you for this challenge!\nHere's hoping you took some business ethics classes during your time there...");
		printf("\nDo keep in mind that this is a stable business where the revenue stream is very constant.");
		printf("\nThis may sound great at first but be warned: this may not be enough to keep the business afloat");
		printf("\nshould unexpected expenses arise. You may have to cut corners sooner or later.");
		printf("\nA word of advice from your father: this is a very unpredictable business that is very subject to");
		printf("\npolitical whims. Try to do everything you can to keep the Republican Party in power here in Springfield.");
		printf("\nGood luck. You're gonna need it.\n\n");		
		printf("-----------------------------------------------------------------------------------\n\n");
		
		int intArr[20]; // a "master" array that will be used over and over in Nuclear Power Plant, contains important int values
		intArr[0] = 1; // round count
		intArr[1] = 0; // to jail? 0 by default, 1 if sent to jail
		intArr[2] = 20; // ACTUAL tax rate this year. resets every round (set = to the DEFAULT)
		intArr[3] = 20; // BASE tax rate this year. value at the very start of the game is 20
		intArr[4] = 1; // counter that increases at a constant rate with each new round up to a max of 100. used to make the odds of bad fates more likely as game progresses.
		intArr[5] = 0; // expected donation for each election. Increments by 5 with each election (every 4 years) including the very first one
		intArr[6] = 1; // keeping track of who won the latest election. 1 for Republicans or 2 for Democrats. set to 1 at start of game
		intArr[7] = 0; // how much the player donates each election. resets every election
		intArr[8] = 0; // possible max value for Catastrophe. increases by a set amount each iteration.
		intArr[9] = 0; // possible max value for Good Fortune. increases by a set amount each iteration.
		intArr[10] = 0; // possible max value for Wild Card. increases by a set amount each iteration.
		intArr[11] = 0; // tax increase in % after Democrats win. increases by a set % which equals said set % * 4 loss in balance across 4 rounds/one election cycle
		intArr[12] = 0; // how many active loans the player has. max value of 2 at any given time
		intArr[13] = -1; // repayment round counter for 1st loan. set to -1 if no active 1st loan
		intArr[14] = -1; // repayment round counter for 2nd loan. set to -1 if no active 2nd loan
		intArr[15] = 0; // how many years 1st loan repayments will last. value depends on which option player chose
		intArr[16] = 0; // how many years 2nd loan repayments will last. value depends on which option player chose
		
		double doubleArr[25]; // a "master" array that will be used over and over in Nuclear Power Plant, contains important double values
		doubleArr[0] = 1; // balance. starting value: 1 (million)
		doubleArr[1] = 100; // revenue. default value is 100. resets every round. Possible Idea: adjust this to lengthen/shorten game? e.g. ask user which difficulty preferred and change this value accordingly
		doubleArr[2] = 20; // ACTUAL wages paid this year. resets (set = to the DEFAULT) every round
		doubleArr[3] = 20; // ACTUAL waste management paid this year. resets (set = to the DEFAULT) every round
		doubleArr[4] = 25; // ACTUAL operating costs paid this year. resets (set = to the DEFAULT) every round
		doubleArr[5] = 20; // BASE wages this year. value at the very start of the game is 20
		doubleArr[6] = 20; // BASE waste management this year. value at the very start of the game is 20
		doubleArr[7] = 25; // BASE operating costs this year. value at the very start of the game is 25 
		doubleArr[8] = 0; // total amount of revenue decrease for the upcoming round. resets every round after revenue calculations
		doubleArr[9] = 0; // net non-revenue balance change tracker. sole purpose is for the player's convenience (i.e. to let them view how much their balance changed in total throughout the round). resets to 0 at start of every round
		doubleArr[10] = 0; // start of year balance tracker. no actual practical usage in the code - only used to display info to the player. set equal to current balance at start of every round
		doubleArr[12] = 0; // wages increase in $ after Democrats win. increases by a set % of balance at time of election loss which equals said % * 4 loss in balance across 4 rounds/one election cycle
		doubleArr[13] = 0; // waste management increase in $ after Democrats win. increases by a set % of balance at time of election loss which equals said % * 4 loss in balance across 4 rounds/one election cycle
		doubleArr[14] = 0; // operating costs increase in $ after Democrats win. increases by a set % of balance at time of election loss which equals said % * 4 loss in balance across 4 rounds/one election cycle
		doubleArr[15] = 0; // 1st loan amount. initially set to principal then divided by # many years * interest rate. this will be the amount user pays yearly for # years
		doubleArr[16] = 0; // 2nd loan amount. initially set to principal then divided by # many years * interest rate. this will be the amount user pays yearly for # years
		doubleArr[17] = 0; // total current loan balance (1st loan + 2nd loan). max value is 100.
		doubleArr[18] = 0; // variable to keep track of 1st loan principal amount
		doubleArr[19] = 0; // variable to keep track of 2nd loan principal amount
		
		while (1) // infinite loop. balance will be periodically checked and used as the break condition once it hits negative
		{
			doubleArr[10] = doubleArr[0]; // setting start of year balance tracker equal to current balance at the start of each round
			
			// REVENUE
			
			doubleArr[1] -= doubleArr[8]; // revenue reset
			printf("Year %d\tThis Year's Revenue: $%.2lf million\tCurrent Balance: $%.2lf million", intArr[0], doubleArr[1], doubleArr[0]);
			
			printf("\n\n---------------");
			
			
			// "RANDOM" EVENTS
			
			printf("\n\nEvents That Took Place This Year:");
			
			randomEvent(intArr, doubleArr);
			
			printf("\n\n---------------");
			
			
			// TAXES
			
			printf("\n\nThis Year's Official Tax Rate: %d%%", intArr[2]);
			printf("\nThis Year's Expected Taxes (in $): $%.2lf million", (intArr[2] / 100.0) * doubleArr[1]);
			Taxes(intArr, doubleArr);
			double taxesPaidIn$ = doubleArr[1] * (intArr[2]/100.0);
			doubleArr[1] -= taxesPaidIn$;
			
			printf("\nTaxes You Paid This Year (in %%): %d%%", intArr[2]);
			printf("\nTaxes You Paid This Year (in $): $%.2lf million", taxesPaidIn$);
			
			printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
			printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
			if (doubleArr[0] < 0)
			{
				printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
			}
			
			if (intArr[1] == 1)
			{
				printf("\n\nYOU HAVE BEEN CAUGHT BY THE IRS AND SENTENCED TO PRISON FOR TAX FRAUD! (You lasted %d years.)", intArr[0]);
				break;
			}
			
			printf("\n\n---------------");
			
			
			// WAGES
			
			printf("\n\nYearly Wages: $%.2lf million", doubleArr[2]);
			Wages(intArr, doubleArr);
			doubleArr[1] -= doubleArr[2];
			printf("\n\nWages You Paid This Year: $%.2lf million", doubleArr[2]);
			
			printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
			printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
			if (doubleArr[0] < 0)
			{
				printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
			}
			
			printf("\n\n---------------");
			
			
			// WASTE MANAGEMENT
		
			printf("\n\nYearly Waste Management: $%.2lf million", doubleArr[3]);
			WasteManagement(intArr, doubleArr);
			doubleArr[1] -= doubleArr[3];
			printf("\n\nWaste Management You Paid This Year: $%.2lf million", doubleArr[3]);
			
			printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
			printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
			if (doubleArr[0] < 0)
			{
				printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
			}
			
			printf("\n\n---------------");
			
			
			// OPERATING COSTS
			
			printf("\n\nYearly Operating Costs: $%.2lf million", doubleArr[4]);
			OperatingCosts(intArr, doubleArr);
			doubleArr[1] -= doubleArr[4];
			printf("\n\nOperating Costs You Paid This Year: $%.2lf million", doubleArr[4]);
			
			printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
			printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
			if (doubleArr[0] < 0)
			{
				printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
			}
			
			printf("\n\n---------------");
			
			
			// POLITICAL CONTRIBUTIONS
			
			if (intArr[0] % 4 == 0)
			{
				if (doubleArr[0] < 1)
				{
					printf("Sorry! You do not have enough money to donate to the Republican Party! It's a millionaires and billionaires only club, bud");
					intArr[7] = 0; // resetting donation amount here outside of the PoliticalContributions function because the player wasn't able to call it!
				}
				else
				{
					PoliticalContributions(intArr, doubleArr);
				}
				
				printf("\n\nYour Political Contributions This Election: $%d million", intArr[7]);
				doubleArr[9] -= intArr[7];
				doubleArr[0] -= intArr[7];
				
				printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
				printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
				if (doubleArr[0] < 0)
				{
					printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
				}
				
				printf("\n\n---------------");
			}
			
			
			// LOANS
			
			printf("\n");
			
			Loans(intArr, doubleArr);
			
			printf("\n\n---------------");
			
			
			// END OF YEAR REPORT & RESETTING VARIABLES
			
			doubleArr[0] += doubleArr[1]; // adds whatever's left of the revenue to the balance. note that revenue can be negative!
			// Non-revenue balance changes will be added to/subtracted from the balance throughout the round so no need for a one-liner here!
			
			printf("\n\nBalance At Start of Year %d: $%.2lf million", intArr[0], doubleArr[10]);
			printf("\n\nRemaining Revenue After All Expenses: $%.2lf million", doubleArr[1]);
			printf("\nBalance Changes This Year (Fines, Repairs, Donations etc.): $%.2lf million", doubleArr[9]);
			printf("\nNet Change in Balance: $%.2lf million", doubleArr[1] + doubleArr[9]);
			printf("\n\nBalance At End of Year %d: $%.2lf million", intArr[0], doubleArr[0]);
			printf("\n\n-----------------------------------------------------------------------------------\n\n");
			if (doubleArr[0] < 0) // Game over if balance hits negative!
			{
				printf("I DECLARE BANKRUPTCY! (You lasted %d years.)", intArr[0]);
				break;
			}
			
			doubleArr[1] = 100; // revenue reset
			intArr[2] = intArr[3]; // tax rate reset
			doubleArr[2] = doubleArr[5]; // wages reset
			doubleArr[3] = doubleArr[6]; // waste management reset
			doubleArr[4] = doubleArr[7]; // operating costs reset
			doubleArr[9] = 0; // net non-revenue balance change tracker reset
			
			intArr[0]++; // round count increment
			if (intArr[4] < 100) 
			{
				intArr[4] += 2.5; // adjust this value to make game harder/go faster
			}
		} // end of while(1) loop which contains 99% of the code for Nuclear Power Plant Simulator

		do
		{
			printf("Would you like to play again? Enter 1 for Yes or 0 for No: ");
			scanf("%d", &userChoice1);
		}
		while (userChoice1 != 0 && userChoice1 != 1);
	} // "official" end point of Nuclear Power Plant Simulator

	return 0;
}

void randomEvent(int intArr[], double doubleArr[])
{
	if (intArr[0] >= 4 && intArr[0] % 2 == 0) // From Round 4 onwards, Catastrophe strikes every 2 rounds
	{
		printf("\n");
		
		intArr[8] += 8; // increasing the possible range of values by a set amount with each new Catastrophe
		int promptSelection = rand() % 10; // randomly selecting which message will be used
		switch (promptSelection)
		{
			case 0:
				printf("\nYour workers have gone on strike! After hours of tense negotiations,");
				printf("\nyou've agreed to buy them all Amazon gift cards and free Chipotle for a month.");
				break;
			case 1:
				printf("\nNUCLEAR MELTDOWN! No one was harmed, but the same can't be said about your wallet.");
				break;
			case 2:
				printf("\nAn earthquake has struck Springfield, costing us a fortune in repairs! At least the reactor is still intact.");
				break;
			case 3:
				printf("\nYour chief financial officer has been caught embezzling company funds for over a decade!");
				printf("\nTurns out he never went to Harvard...or college either, for that matter.");
				break;
			case 4:
				printf("\nYour investment in BitConnect disappeared overnight as it turns out to be a Ponzi scheme. Who could have seen it coming!?!?");
				break;
			case 5:
				printf("\nIn a bid to boost revenue, you've decided to hire the local mafia to harass your hydroelectric power plant competitors!");
				break;
			case 6:
				printf("\nUnder the influence of an unidentified white powder, you blew millions of company funds in one night at the local casino.");
				break;
			case 7:
				printf("\nBoard of directors have voted to donate a large sum to the election campaign of an unnamed pro-nuclear candidate.");
				break;
			case 8:
				printf("\nFulfilling a lifelong dream of having a building named after you, you've decided to donate a fortune to the University of Springfield.");
				printf("\nIn return, they've agreed to rename the university's main bus stop in your honor.");
				break;
			case 9:
				printf("\nDue to the heaters suddenly going out one freezing day in winter, you and your employees burn paper cash to stay warm."); 
				break;
		}
		
		int catastropheVal = (rand() % intArr[8]) + intArr[0];
		doubleArr[9] -= catastropheVal;
		doubleArr[0] -= catastropheVal;
		printf("\n(Balance decreased by $%d million)", catastropheVal);
		printf("\nCurrent Balance: $%.2lf million", doubleArr[0]);
		if (doubleArr[0] < 0)
		{
			printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
		}
	}
	
	if (intArr[0] >= 6 && intArr[0] % 4 == 0) // From Round 6 onwards, Good Fortune strikes every 4 rounds
	{
		printf("\n");
		
		intArr[9] += 2; // increasing the possible range of values by a set amount with each new Good Fortune
		int promptSelection = rand() % 10; // randomly selecting which message will be used
		switch (promptSelection)
		{
			case 0:
				printf("\nBelieving that the future is green energy, the citizens of Springfield have collectively invested millions in your company!");
				break;
			case 1:
				printf("\nYour longlost half brother has recently passed away. Strangely enough, he has decided to give most of his considerable wealth to you in his will!");
				break;
			case 2:
				printf("\nAfter decades of playing the lottery to no avail, you have finally struck gold! Finally, all those nights spent praying have born fruit!");
				break;
			case 3:
				printf("\nThe Trump Organization has decided to settle the lawsuit regarding your Trump University diploma for a large lump sum!");
				break;
			case 4:
				printf("\nYou've finally found a buyer on eBay for your father's prehistoric artifacts!");
				break;
			case 5:
				printf("\nPerhaps finally seeing the light and the errors in their ways, Springfield Petroleum, LLC has decided to buy a large stake in your company!");
				break;
			case 6:
				printf("\nYou've decided to cash out on your Bitcoins after they reached a historic high last Friday...right before losing 20%% of its value the following day!");
				break;
			case 7:
				printf("\nSaudis looking to diversify their portfolio have poured millions into your company. How they came to this decision is not known!"); 
				break;
			case 8:
				printf("\nIn the midst of the Great COVID-19 Depression, Congress has provided your company millions in emergency relief funds!");
				break;
			case 9:
				printf("\nYour board of directors have voted to sell a sizeable chunk of unused company land, citing a pressing need for cash injections!");
				break;
		}
		
		int goodFortuneVal = (rand() % intArr[9]) + intArr[0];
		doubleArr[9] += goodFortuneVal;
		doubleArr[0] += goodFortuneVal;
		printf("\n(Balance increased by $%d million)", goodFortuneVal);
		printf("\nCurrent Balance: $%.2lf million", doubleArr[0]);
		if (doubleArr[0] < 0)
		{
			printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
		}
	}
	
	if (intArr[0] >= 8 && intArr[0] % 6 == 0) // From Round 8 onwards, Wild Card strikes every 6 rounds
	{
		printf("\n");
		int userChoice; // variable that records the user's choice whether they choose to take up the wild card or not
		intArr[10] += 4; // increasing the possible range of values by a set amount with each new Wild Card
		int wildCardVal = (rand() % intArr[10]) + intArr[0]; // determining the value of this Wild Card
		
		int promptSelection = rand() % 4; // randomly selecting which message will be used
		switch (promptSelection)
		{
			case 0:
				userChoice = promptUser("A Nigerian prince has promised to send you millions if you offered him legal assistance in accessing his bank account.\nWould you like to take up this offer?\n");
				break;
			case 1:
				userChoice = promptUser("Your close friend has invited you to join him in investing in a \"new, promising\" crytocurrency.\nWould you like to take up this offer?\n");
				break;
			case 2:
				userChoice = promptUser("A hedge fund has offered crazy returns in exchange for your trust (and your money, of course).\nWould you like to take up this offer?\n");
				break;
			case 3:
				userChoice = promptUser("Your financial advisor has singled out a \"new and very promising\" startup she thinks this company should invest in.\nWould you like to take up this offer?\n");
				break;
		}
		
		if (userChoice == 1)
		{
			int wildCardChance = rand() % 101;
			if (wildCardChance < 51)
			{
				doubleArr[0] += wildCardVal;
				doubleArr[9] += wildCardVal;
				printf("\nThis offer has made us even richer! Good call!");
				printf("\n(Balance increased by $%d million)", wildCardVal);
				printf("\nCurrent Balance: $%.2lf million", doubleArr[0]);
				if (doubleArr[0] < 0)
				{	
					printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
				}
			}
			else
			{
				doubleArr[0] -= wildCardVal;
				doubleArr[9] -= wildCardVal;
				printf("\nThis offer flopped! Board of directors and investors question your acumen...");
				printf("\n(Balance decreased by $%d million)", wildCardVal);
				printf("\nCurrent Balance: $%.2lf million", doubleArr[0]);
				if (doubleArr[0] < 0)
				{	
					printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
				}
			}
		}
	}
}

void Taxes(int intArr[], double doubleArr[]) 
{	
	if (promptUser("Would you like to commit tax fraud this year (result: $ saved!) and hope you don't get sent to prison?") == 1) // user wants to commit fraud this round
	{
		int fraudVal;
		printf("\n");
		do
		{
			printf("How much taxes (in %%) would you like to pay instead this year? Enter a value from 1 up to 1 less than the tax rate: ");
			scanf("%d", &fraudVal);
		}
		while (fraudVal < 1 || fraudVal > intArr[2] - 1); 
	
		double fraudValInDouble = fraudVal;
		double taxReductionAsPortionOfTotal = (intArr[2] - fraudValInDouble) / intArr[2] * 100.0; // portionOfTax equals 65.74, 54.23412 etc.
		if (taxReductionAsPortionOfTotal >= 100 - rand() % intArr[4]) // this means that until Round 5, the player has a 0% chance of getting sent to jail 
		// Here's why. rand() % 5 generates a random numbesr up to 4 so 100 - 4 = 96 is the smallest possible value in Round 4. However, the player
		// can only pay as little as 1% in taxes which equates to a 95% taxReductionAsPortionOfTotal.
		// paying only 1% in taxes is a 19% tax reduction. 19%/20% = 95%. Since 95% is less than 96% (the lowest possible value for the value on the right side
		// of the inequality in Round 4), it is IMPOSSIBLE for the user to be sent to prison even if they pay only 1% in taxes for the first 4 rounds!
		// This is like a secret built-in cheat code/exploit in a way...
		{
			intArr[1] = 1;
		}
		
		intArr[2] = fraudVal;
		
		PRDisaster(intArr, doubleArr, taxReductionAsPortionOfTotal, "Headlines read: Leaked documents show Springfield Nuclear Power Plant paid a pittance in taxes this year! Boycott movement grows.");
	}
}

void Wages(int intArr[], double doubleArr[])
{
	if (promptUser("Would you like to pay out less wages and worker benefits this year (result: $ saved!) and hope productivity doesn't plummet all too much?") == 1)
	{
		int wageCuts;
		printf("\n");
		do
		{
			printf("How much less (in %%) wages and worker benefits would you like to pay this year? Enter a value from 1 up to 50: ");
			scanf("%d", &wageCuts);
		}
		while (wageCuts < 1 || wageCuts > 50);
		
		doubleArr[2] = doubleArr[2] * ( (100 - wageCuts) / 100.0 ); // reduces wages for this round by however many % user specified
				
		// "CONSISTENT" PENALTY OF BAD DECISION
		
		double halfOfWagesSkimped = (doubleArr[5] - doubleArr[2]) * 0.5; // will be used as the upper bound of possible range of revenue decrease
		int wagesSkimpedInInt = doubleArr[5] - doubleArr[2] + 1; // must be saved in int to be used with rand in the upcoming line of code. also have to + 1 because rand() % 0 will generate an error
		double penalty = ( rand() % (wagesSkimpedInInt + 1) ) + halfOfWagesSkimped;
		// this value in the range of 0.5x - 1.5x (of however much the user saved from making the bad decision this round) will be subtracted
		// from the balance. this basically acts as a gamble for taking the bad decision with the chance of costing the user more than they saved, resulting in a net negative
		doubleArr[8] += penalty;
		// the said subtraction from the balance
		printf("\nAs a result of the recent wage and worker benefits cuts, morale in your workface has taken a hit and so has productivity!");
		printf("\nWho would have thunk that employees enjoy receiving bonuses!?!?!?");
		printf("\n(Revenue decreased by $%.2lf million next year)", penalty);

		// "INCONSISTENT" PENALTY OF BAD DECISION
		
		double percentOfTotal = (doubleArr[5] - doubleArr[2]) / doubleArr[5] * 100; // gives wages skimped for this round in terms of % (portion) of the total wages
		PRDisaster(intArr, doubleArr, percentOfTotal, "Headlines read: Springfield Power Plant workers increasingly overworked and underpaid, reports allege");
	}
}

void WasteManagement(int intArr[], double doubleArr[])
{
	if (promptUser("Would you like to dump waste into the river instead of proper disposal this year (result: $ saved!) and hope the fine isn't too hefty?") == 1)
	{
		int wasteCuts;
		printf("\n");
		do
		{
			printf("How much less (in %%) would you like to pay for waste management this year? Enter a value from 1 up to 50: ");
			scanf("%d", &wasteCuts);
		}
		while (wasteCuts < 1 || wasteCuts > 50);
		
		doubleArr[3] = doubleArr[3] * ( (100 - wasteCuts) / 100.0 ); // reduces wages for this round by however many % user specified
				
		// "CONSISTENT" PENALTY OF BAD DECISION
		
		double halfOfWasteCuts = (doubleArr[6] - doubleArr[3]) * 0.5; // will be used as the upper bound of possible range of revenue decrease
		int wasteCutsInInt = doubleArr[6] - doubleArr[3] + 1; // must be saved in int to be used with rand in the upcoming line of code. also have to + 1 because rand() % 0 will generate an error
		double penalty = ( rand() % (wasteCutsInInt + 1) ) + halfOfWasteCuts;
		// this value in the range of 0.5x - 1.5x (of however much the user saved from making the bad decision this round) will be subtracted
		// from the balance. this basically acts as a gamble for taking the bad decision with the chance of costing the user more than they saved, resulting in a net negative
		doubleArr[0] -= penalty;
		doubleArr[9] -= penalty;
		// the said subtraction from the balance
		printf("\nYou have been fined by the EPA for your improper waste disposal!");
		printf("\n(Balance decreased by $%.2lf million)", penalty);

		// "INCONSISTENT" PENALTY OF BAD DECISION
		
		double percentOfTotal = (doubleArr[6] - doubleArr[3]) / 20 * 100; // gives wages skimped for this round in terms of % (portion) of the total wages
		PRDisaster(intArr, doubleArr, percentOfTotal, "Headlines read: Latest study links growing number of mutated fish in Springfield to nuclear waste dumping. Springfield Nuclear Power Plant denies study's claims");
	}
}

void OperatingCosts(int intArr[], double doubleArr[])
{
	if (promptUser("Would you like to cut corners wherever your imagination permits (result: $ saved!) and hope no accidents occur (WARNING: WISHFUL THINKING DETECTED)?") == 1)
	{
		int OPCuts;
		printf("\n");
		do
		{
			printf("How much less (in %%) would you like to pay in operating costs this year? Enter a value from 1 up to 50: ");
			scanf("%d", &OPCuts);
		}
		while (OPCuts < 1 || OPCuts > 50);
		
		doubleArr[4] = doubleArr[4] * ( (100 - OPCuts) / 100.0 ); // reduces wages for this round by however many % user specified
				
		// "CONSISTENT" PENALTY OF BAD DECISION
		
		double halfOfOPCuts = (doubleArr[7] - doubleArr[4]) * 0.5; // will be used as the upper bound of possible range of revenue decrease
		int OPCutsInInt = doubleArr[7] - doubleArr[4] + 1; // must be saved in int to be used with rand in the upcoming line of code. also have to + 1 because rand() % 0 will generate an error
		double penalty = ( rand() % (OPCutsInInt + 1) ) + halfOfOPCuts;
		// this value in the range of 0.5x - 1.5x (of however much the user saved from making the bad decision this round) will be subtracted
		// from the balance. this basically acts as a gamble for taking the bad decision with the chance of costing the user more than they saved, resulting in a net negative
		doubleArr[0] -= penalty;
		doubleArr[9] -= penalty;
		// the said subtraction from the balance
		printf("\nYour cheapskating ways have surprisingly resulted in workplace accidents! Repairs are gonna cost ya...");
		printf("\n(Balance decreased by $%.2lf million)", penalty);

		// "INCONSISTENT" PENALTY OF BAD DECISION
		
		double percentOfTotal = (doubleArr[7] - doubleArr[4]) / 25 * 100; // gives wages skimped for this round in terms of % (portion) of the total wages
		PRDisaster(intArr, doubleArr, percentOfTotal, "Headlines read: Investor confidence in Springfield Nuclear Power Plant takes a hit as accidents continue to pile up");
	}
}

void PoliticalContributions(int intArr[], double doubleArr[])
{	
	if (intArr[6] == 2) // if Democrats won the last election, need to restore costs back to their values before the last election's outcome. blank slate essentially
	// no need to adjust the values if Republicans won the last election as status quo was maintained
	// remember that these values on the right sides of the = operators have not been touched since the last election
	// therefore, they still retain the exact values from their last election
	// these values may be changed once more by the end of this iteration depending on the outcome of the election
	{
		intArr[3] -= intArr[11]; 
		doubleArr[5] -= doubleArr[12];
		doubleArr[6] -= doubleArr[13];
		doubleArr[7] -= doubleArr[14];
	}
	intArr[5] += 7.5; // increasing expected donation with each new election
	intArr[7] = 0; // resetting donation amount
		
	printf("\n\nElection year is upon us once more in Springfield!");
	printf("\nYour contributions go a long way in ensuring the pro-business Republican Party stay in power in our city.");
	printf("\nHow many million dollars would you like to donate to the Republicans this election cycle?");
	printf("\nDo keep in mind that you may need to chip in more for each subsequent election due to gradual demographic changes favoring the Democrats: ");
	scanf("%d", &intArr[7]);
	
	while (intArr[7] < 0 || intArr[7] > doubleArr[0])
	{
		printf("Please donate an amount between 0 up to your balance: ");
		scanf("%d", &intArr[7]);
	}
		
	// The user is expected to chip in more and more with each new election
	// If the user chips in equal to or more than expected, Republicans are guaranteed to win
	// If the user chips in less than expected, Republicans have a chance of winning equal to the fraction of the expected amount user chipped in
	// e.g. Election 5 = user should chip in 5 mil. however, user only donated 3 mil. Republicans therefore have a 60% chance (3/5) of winning Election 5
	double donationInDouble = intArr[7];
	double portionOfExpectedDonation = donationInDouble / intArr[5] * 100;
	if (portionOfExpectedDonation >= rand() % 101) // if Republicans win this election, costs stay the same (i.e. nothing changes)
	{	
		// The messages printed out will depend on who won the LAST election
		if (intArr[6] == 2) // if Democrats won the LAST election
		{
			printf("\nRepublicans retake control of Springfield!");
			printf("\nTaxes and other costs have been brought back down after four long years. Long live the GOP!");
			printf("\nPolicies passed by the Republicans:");
			printf("\n> Tax rate for businesses brought back down to a reasonable %d%%!", intArr[3]);
			printf("\n> Minimum wage has been brought back down to $10/hour in Springfield, saving you $%.2lf million each year!", doubleArr[12]);
			printf("\n> Waste management costs decrease by $%.2lf million a year thanks to new more lax environmental regulations!", doubleArr[13]);
			printf("\n> Operating costs decrease by $%.2lf million a year as Congress embarks on a journey to pay off the national debt!", doubleArr[14]);
			
			// No need to restore the costs back to their pre-election values as this was already done a few lines ago
		}
		else // if Republicans won the LAST election
		{
			printf("\nRepublicans retain control over Springfield!");
			printf("\nTaxes and other costs remain at a stable level. Long live the GOP!");
		}
		
		intArr[6] = 1; // marking down that Republicans have won THIS election
	}
	else // if Democrats win this election, increase costs (except operating costs). 
	{
		// The total cost of losing an election will be AT LEAST 34% of the player's balance at the time of the start of the election. This -34% loss will be spread out across 4 rounds.
		// The 34% net loss will be spread out like this: taxes will take away 16% of balance, wages 8%, waste management 6% and operating costs 4%;
		// See notes at the beginning for more detail
		// Doesn't really matter how it's spread out to be honest because these are percentages of the player's total balance at time of election, not of the actual costs themselves
		// Just spreading it out to make the game feel more "real"
		intArr[11] = 4; // taxes increase in %
		intArr[3] += intArr[11]; // adding this tax % increase to the base tax %
		
		// printf("\n%% tax increase: %d", intArr[11]); <- print statement used to test if code is working
		
		doubleArr[12] = (doubleArr[0] * 0.02); // wages increase in $
		if (doubleArr[12] < 1) // if wages increase each round in $mil is less than 1 mil (which means player balance must be dangerously low)
		{
			doubleArr[12] = 1; // manually set it to 1 mil as to speed up game/ramp up difficulty
		}
		doubleArr[5] += doubleArr[12]; // adding this wages increase to the base wage amount
		
		// printf("\nwage increase in $: %.2lf, as %% of total: %.2lf", doubleArr[12], doubleArr[12] / doubleArr[0] * 100); <- print statement used to test if code is working
		
		doubleArr[13] = (doubleArr[0] * 0.015); // waste management increase in $
		if (doubleArr[13] < 1) // if waste management increase each round in $mil is less than 1 mil (which means player balance must be dangerously low)
		{
			doubleArr[13] = 1; // manually set it to 1 mil as to speed up game/ramp up difficulty
		}
		doubleArr[6] += doubleArr[13]; // adding this waste management increase to the base wage amount
		
		// printf("\nwaste man increase in $: %.2lf, as %% of total: %.2lf", doubleArr[13], doubleArr[13] / doubleArr[0] * 100); <- print statement used to test if code is working
		
		doubleArr[14] = (doubleArr[0] * 0.01); // operating costs increase in $
		if (doubleArr[14] < 1) // if operating costs increase each round in $mil is less than 1 mil (which means player balance must be dangerously low)
		{
			doubleArr[14] = 1; // manually set it to 1 mil as to speed up game/ramp up difficulty
		}
		doubleArr[7] += doubleArr[14]; // adding this operating costs increase to the base wage amount
		
		// printf("\nOP costs increase in $: %.2lf, as %% of total: %.2lf", doubleArr[14], doubleArr[14] / doubleArr[0] * 100); <- print statement used to test if code is working
		
		// The messages printed out will depend on who won the last election
		if (intArr[6] == 2) // if Democrats won the LAST election
		{
			printf("\nDemocrats retain control over Springfield...tis a sad day for us business owners :(");
			printf("\nTaxes and other costs remain at a high level. We must donate more to the GOP next time!");
		}
		else // if Republicans won the LAST election
		{
			printf("\nDemocrats retake control of Springfield...tis a sad day for us business owners :(");
			printf("\nTaxes and other costs have climbed thanks to their so-called progressive policies. We must donate more to the GOP next time!");
			printf("\nPolicies passed by the Democrats:");
			printf("\n> Tax rate for businesses raised by a whopping %d%% to fund S O C I A L I S T measures (OH NOES!)", intArr[11]);
			printf("\n> Minimum wage has been increased to $15/hour in Springfield, costing you $%.2lf million more each year...", doubleArr[12]);
			printf("\n> Waste management costs increase by $%.2lf million a year due to stricter environmental regulations", doubleArr[13]);
			printf("\n> Operating costs increase by $%.2lf million a year due to rampant inflation caused by Congress's reckless spending", doubleArr[14]);
		}
		
		intArr[6] = 2; // marking down that Democrats have won THIS election
	}
}

void Loans(int intArr[], double doubleArr[])
{
	printf("\nWelcome to First National Bank Springfield! Here are the terms for taking out a loan with us:");
	printf("\n1) You may only have 2 active loans at any given time");
	printf("\n2) You may not take out more than $100 million in total across both loans");
	printf("\n3) Repayment begins the following year and continue yearly until the loan is paid off");
	printf("\n4) No prepayments available! We're not lending to you for free...or for cheap, for that matter");
	printf("\n\nRates for your first loan:");
	printf("\n5 Year Payment Plan @ 15%% Interest");
	printf("\n10 Year Payment Plan @ 20%% Interest");
	printf("\n15 Year Payment Plan @ 25%% Interest");
	printf("\n\nRates for your second loan:");
	printf("\n5 Year Payment Plan @ 20%% Interest");
	printf("\n10 Year Payment Plan @ 25%% Interest");
	printf("\n15 Year Payment Plan @ 30%% Interest");
	
	if (intArr[12] == 0 && doubleArr[17] < 100) // checking whether users can take out loans. if so, how many and how much?
	{
		printf("\n");
		int userChoice = promptUser("Would you like to take out a loan?");
		if (userChoice == 1)
		{
			intArr[12]++;
			
			do
			{
				printf("\nHow much would you like to take out for this loan? (Possible Range: $0.1-$100 million): ");
				scanf("%lf", &doubleArr[15]);
			}
			while (doubleArr[15] < 0.1);
			doubleArr[18] = doubleArr[15];
			doubleArr[17] += doubleArr[15];
			
			int loan1Choice = loan1Option(intArr, doubleArr);
			
			if (loan1Choice == 1)
			{
				doubleArr[0] += doubleArr[15]; // adding loan principal to player's balance before interest and repayment are calculated
				printf("\nFirst National Bank Springfield has added $%.2lf million to your balance!", doubleArr[15]);
				printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
				printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
				if (doubleArr[0] < 0)
				{
					printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
				}
				
				doubleArr[15] /= 5;
				doubleArr[15] *= 1.15;
				intArr[13] = 0;
				intArr[15] = 5;
			}
			else if (loan1Choice == 2)
			{
				doubleArr[0] += doubleArr[15]; // adding loan principal to player's balance before interest and repayment are calculated
				printf("\nFirst National Bank Springfield has added $%.2lf million to your balance!", doubleArr[15]);
				printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
				printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
				if (doubleArr[0] < 0)
				{
					printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
				}
				
				doubleArr[15] /= 10;
				doubleArr[15] *= 1.2;
				intArr[13] = 0;
				intArr[15] = 10;
			}
			else
			{
				doubleArr[0] += doubleArr[15]; // adding loan principal to player's balance before interest and repayment are calculated
				printf("\nFirst National Bank Springfield has added $%.2lf million to your balance!", doubleArr[15]);
				printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
				printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
				if (doubleArr[0] < 0)
				{
					printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
				}
				
				doubleArr[15] /= 15;
				doubleArr[15] *= 1.25;
				intArr[13] = 0;
				intArr[15] = 15;
			}
		}
		
		printf("\n");
		int userChoice2 = promptUser("Would you like to take out another loan?");
		if (userChoice2 == 1)
		{
			intArr[12]++;
			
			do
			{
				printf("\nHow much would you like to take out for your this loan? (Possible Range: $0.1-$%.2lf million): ", 100 - doubleArr[17]);
				scanf("%lf", &doubleArr[16]);
			}
			while (doubleArr[16] < 0.1 || doubleArr[16] > 100 - doubleArr[17]);
			doubleArr[19] = doubleArr[16];
			doubleArr[17] += doubleArr[16];
			
			int loan2Choice = loan2Option(intArr, doubleArr);
			
			if (loan2Choice == 1)
			{
				doubleArr[0] += doubleArr[16]; // adding loan principal to player's balance before interest and repayment are calculated
				printf("\nFirst National Bank Springfield has added $%.2lf million to your balance!", doubleArr[16]);
				printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
				printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
				if (doubleArr[0] < 0)
				{
					printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
				}
				
				doubleArr[16] /= 5;
				doubleArr[16] *= 1.2;
				intArr[14] = 0;
				intArr[16] = 5;
			}
			else if (loan2Choice == 2)
			{
				doubleArr[0] += doubleArr[16]; // adding loan principal to player's balance before interest and repayment are calculated
				doubleArr[0] += doubleArr[16]; // adding loan principal to player's balance before interest and repayment are calculated
				printf("\nFirst National Bank Springfield has added $%.2lf million to your balance!", doubleArr[16]);
				printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
				printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
				if (doubleArr[0] < 0)
				{
					printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
				}
				
				doubleArr[16] /= 10;
				doubleArr[16] *= 1.25;
				intArr[14] = 0;
				intArr[16] = 10;
			}
			else
			{
				doubleArr[0] += doubleArr[16]; // adding loan principal to player's balance before interest and repayment are calculated
				doubleArr[0] += doubleArr[16]; // adding loan principal to player's balance before interest and repayment are calculated
				printf("\nFirst National Bank Springfield has added $%.2lf million to your balance!", doubleArr[16]);
				printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
				printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
				if (doubleArr[0] < 0)
				{
					printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
				}
				
				doubleArr[16] /= 15;
				doubleArr[16] *= 1.3;
				intArr[14] = 0;
				intArr[16] = 15;
			}
		}
	}
	else if (intArr[12] == 1 && doubleArr[17] < 100) 
	{
		if (intArr[13] == -1) // if first loan is inactive, use first loan's "slot" (i.e. utilize first loan's variables)
		{
			printf("\n");
			int userChoice = promptUser("Would you like to take out your another loan?");
			
			if (userChoice == 1)
			{
				intArr[12]++;
					
				do
				{
					printf("\nHow much would you like to take out for your this loan? (Possible Range: $0.1-$%.2lf million): ", 100 - doubleArr[17]);
					scanf("%lf", &doubleArr[15]);
				}
				while (doubleArr[15] < 0.1 || doubleArr[15] > 100 - doubleArr[17]);
				doubleArr[18] = doubleArr[15];
				doubleArr[17] += doubleArr[15];
						
				int loan2Choice = loan2Option(intArr, doubleArr);
			
				if (loan2Choice == 1)
				{
					doubleArr[0] += doubleArr[15]; // adding loan principal to player's balance before interest and repayment are calculated
					printf("\nFirst National Bank Springfield has added $%.2lf million to your balance!", doubleArr[15]);
					printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
					printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
					if (doubleArr[0] < 0)
					{
						printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
					}
					
					doubleArr[15] /= 5;
					doubleArr[15] *= 1.2;
					intArr[13] = 0;
					intArr[15] = 5;
				}
				else if (loan2Choice == 2)
				{
					doubleArr[0] += doubleArr[15]; // adding loan principal to player's balance before interest and repayment are calculated
					printf("\nFirst National Bank Springfield has added $%.2lf million to your balance!", doubleArr[15]);
					printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
					printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
					if (doubleArr[0] < 0)
					{
						printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
					}
					
					doubleArr[15] /= 10;
					doubleArr[15] *= 1.25;
					intArr[13] = 0;
					intArr[15] = 10;
				}
				else
				{
					doubleArr[0] += doubleArr[15]; // adding loan principal to player's balance before interest and repayment are calculated	
					printf("\nFirst National Bank Springfield has added $%.2lf million to your balance!", doubleArr[15]);
					printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
					printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
					if (doubleArr[0] < 0)
					{
						printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
					}
					
					doubleArr[15] /= 15;
					doubleArr[15] *= 1.3;
					intArr[13] = 0;
					intArr[15] = 15;
				}
			}
		}
		else // if this point is reached, it means that first loan is active and so 2nd loan's "slot" should be used instead (i.e. utlize second loan's variables)
		{
			printf("\n");
			int userChoice = promptUser("Would you like to take out another loan?");
			
			if (userChoice == 1)
			{
				intArr[12]++;
			
				do
				{
					printf("\nHow much would you like to take out for your this loan? (Possible Range: $0.1-$%.2lf million): ", 100 - doubleArr[17]);
					scanf("%lf", &doubleArr[16]);
				}
				while (doubleArr[16] < 0.1 || doubleArr[16] > 100 - doubleArr[17]);
				doubleArr[19] = doubleArr[16];
				doubleArr[17] += doubleArr[16];
			
				int loan2Choice = loan2Option(intArr, doubleArr);
			
				if (loan2Choice == 1)
				{
					doubleArr[0] += doubleArr[16]; // adding loan principal to player's balance before interest and repayment are calculated
					printf("\nFirst National Bank Springfield has added $%.2lf million to your balance!", doubleArr[16]);
					printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
					printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
					if (doubleArr[0] < 0)
					{
						printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
					}
					
					doubleArr[16] /= 5;
					doubleArr[16] *= 1.2;
					intArr[14] = 0;
					intArr[16] = 5;
				}
				else if (loan2Choice == 2)
				{
					doubleArr[0] += doubleArr[16]; // adding loan principal to player's balance before interest and repayment are calculated
					printf("\nFirst National Bank Springfield has added $%.2lf million to your balance!", doubleArr[16]);
					printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
					printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
					if (doubleArr[0] < 0)
					{
						printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
					}
					
					doubleArr[16] /= 10;
					doubleArr[16] *= 1.25;
					intArr[14] = 0;
					intArr[16] = 10;
				}
				else
				{
					doubleArr[0] += doubleArr[16]; // adding loan principal to player's balance before interest and repayment are calculated
					printf("\nFirst National Bank Springfield has added $%.2lf million to your balance!", doubleArr[16]);
					printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
					printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
					if (doubleArr[0] < 0)
					{
						printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
					}
					
					doubleArr[16] /= 15;
					doubleArr[16] *= 1.3;
					intArr[14] = 0;
					intArr[16] = 15;
				}
			}
		}
	}
	else
	{
		printf("\n\nYou may not take out any new loans at this time as your total loan balance is $100 million or you currently have 2 active loans.");
	}
	
	
	if (intArr[13] > 0) // check to see if user needs to make 1st loan payments
	{
		if (intArr[13] <= intArr[15]) // if still have to make payments because # of years isn't reached
		{
			doubleArr[0] -= doubleArr[15];
			doubleArr[9] -= doubleArr[15];
			printf("\n\nPayment %d (Out of %d) for One of Your Loans: $%.2lf million", intArr[13], intArr[15], doubleArr[15]);
			printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
			printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
			if (doubleArr[0] < 0)
			{
				printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
			}
		}
	}
	
	
	if (intArr[14] > 0) // check to see if user needs to make 2nd loan payments
	{
		if (intArr[14] <= intArr[16]) // if still have to make payments because # of years isn't reached
		{
			doubleArr[0] -= doubleArr[16];
			doubleArr[9] -= doubleArr[16];
			printf("\n\nPayment %d (Out of %d) for the Other of Your Loans: $%.2lf million", intArr[14], intArr[16], doubleArr[16]);
			printf("\n\nRemaining Revenue This Year: $%.2lf million", doubleArr[1]);
			printf("\nRemaining Balance: $%.2lf million", doubleArr[0]);
			if (doubleArr[0] < 0)
			{
				printf("\nWARNING: If your balance remains negative at the end of this year after revenue has been added in, you will go BANKRUPT!");
			}
		}
	}
	
	
	if (intArr[13] != -1) // if there is an active 1st loan
	{
		intArr[13]++; // increment year count for 1st loan
	}
	
	if (intArr[13] > intArr[15]) // if 1st loan has reached its life
	{
		intArr[12] -= 1; // reduce number of active loans by 1
		intArr[13] = -1;
		intArr[15] = 0;
		doubleArr[15] = 0;
		doubleArr[17] -= doubleArr[18]; // subtracting current total loan balnace by 1st loan principal (amount originally taken out)
		doubleArr[18] = 0;
	}
	
	if (intArr[14] != -1) // if there is an active 2nd loan
	{
		intArr[14]++; // increment year count for 2nd loan
	}
	
	if (intArr[14] > intArr[16]) // if 2nd loan has reached its life
	{
		intArr[12] -= 1; // reduce number of active loans by 1;
		intArr[14] = -1;
		intArr[16] = 0;
		doubleArr[16] = 0;
		doubleArr[17] -= doubleArr[19]; // subtracting current total loan balnace by 2nd loan principal (amount originally taken out)
		doubleArr[19] = 0;
	}
}
				
void PRDisaster(int intArr[], double doubleArr[], double percentOfTotal, char message[])
{
	if (percentOfTotal >= 100 - ( rand() % (intArr[4] + 1) ) )
	{
		int TenPerOfCurrentBalance = doubleArr[0] * 0.1;
		double penalty = (rand() % TenPerOfCurrentBalance) + 1;
		doubleArr[8] += penalty;
		printf("\nPR DISASTER! %s", message);
		printf("\n(Revenue decreased by $%.2lf million next year)", penalty);
	}
}

int promptUser(char question[]) // returns 1 if yes, 2 if no
{
	char userChoice;
	do
	{
		printf("\n%s Enter Y for Yes or N for No: ", question);
		scanf(" %c", &userChoice);
	}
	while (userChoice != 'Y' && userChoice != 'y' && userChoice != 'N' && userChoice != 'n');
	
	if (userChoice == 'Y' || userChoice == 'y')
	{
		return 1;
	}
	else 
	{
		return 2;
	}
}

int loan1Option(int intArr[], double doubleArr[])
{
	int userChoice;
	printf("\nRates for this loan:");
	
	printf("\n\n5 Year Payment Plan @ 15%% Interest");
	printf("\nExpected Yearly Payment: $%.2lf million", doubleArr[18] / 5 * 1.15);
	printf("\nExpected Total Paid Over Life of Loan: $%.2lf million", doubleArr[18] * 1.15);
	
	printf("\n\n10 Year Payment Plan @ 20%% Interest");
	printf("\nExpected Yearly Payment: $%.2lf million", doubleArr[18] / 10 * 1.2);
	printf("\nExpected Total Paid Over Life of Loan: $%.2lf million", doubleArr[18] * 1.2);
	
	printf("\n\n15 Year Payment Plan @ 25%% Interest");
	printf("\nExpected Yearly Payment: $%.2lf million", doubleArr[18] / 15 * 1.25);
	printf("\nExpected Total Paid Over Life of Loan: $%.2lf million", doubleArr[18] * 1.25);
	
	printf("\n\n");
	do
	{
		printf("Please select which option (1, 2 or 3) you would like: ");
		scanf("%d", &userChoice);
	}
	while (userChoice != 1 && userChoice != 2 && userChoice != 3);
	
	return userChoice;
}

int loan2Option(int intArr[], double doubleArr[])
{
	int userChoice;
	printf("\nRates for this loan:");
	
	printf("\n\n5 Year Payment Plan @ 20%% Interest");
	printf("\nExpected Yearly Payment: $%.2lf million", doubleArr[19] / 5 * 1.2);
	printf("\nExpected Total Paid Over Life of Loan: $%.2lf million", doubleArr[19] * 1.2);
	
	printf("\n\n10 Year Payment Plan @ 25%% Interest");
	printf("\nExpected Yearly Payment: $%.2lf million", doubleArr[19] / 10 * 1.25);
	printf("\nExpected Total Paid Over Life of Loan: $%.2lf million", doubleArr[19] * 1.25);
	
	printf("\n\n15 Year Payment Plan @ 30%% Interest");
	printf("\nExpected Yearly Payment: $%.2lf million", doubleArr[19] / 15 * 1.3);
	printf("\nExpected Total Paid Over Life of Loan: $%.2lf million", doubleArr[19] * 1.3);
	
	printf("\n\n");
	do
	{
		printf("Please select which option (1, 2 or 3) you would like: ");
		scanf("%d", &userChoice);
	}
	while (userChoice != 1 && userChoice != 2 && userChoice != 3);

	return userChoice;
}
