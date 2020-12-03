#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
// TO ENHANCE CANCELLING
int b_i,numb_c;

struct flight{
	int eb; // eco booked
	int bb; // bus booked
	int et;   // economy total
	int bt;   // business total
	int s_ep;
	int s_bp;
	int b_ep;
	int b_bp;
	int m[18];  // high means ordered meals
	int tcost;  
	int bok[18];  // high means booked
	int fid;
	int surgep; // offset of surege pricing
//	int totalb[100];
	int totalb_i;
}f[2];

struct booking{
	int bid;
	int fid;
	int condition;   // 0 cancelled
	int mcond;   // 0 no meals
	char type;   // E economy B business
	int cost;  // cost of booking;
	int seats[18]; // seat numbers;  
	int ns;  // numbe rof seats booked
}b[100];

void init(){
	int i;
	b_i=0;
	for(i=0;i<2;i++){
		f[i].fid=101+i;
		f[i].eb=0;
		f[i].bb=0;
		f[i].bt=6;
		f[i].et=12;
		f[i].s_bp=0;
		f[i].s_ep=0;
		f[i].b_bp=2000;
		f[i].b_ep=1000;
		f[i].surgep=200;
		f[i].totalb_i=0;
//		memset(f[i].totalb,0,(100));     //  *******
		memset(f[i].m,0,(f[i].et+f[i].bt)*sizeof(int));
		memset(f[i].bok,0,(f[i].et+f[i].bt)*sizeof(int));
	}	
}

int book(){
	int i,j,k;
	int cfid,cns,avs,mf=0;
	char ct,qt;
	printf("Enter flight Number : ");
	scanf("%d",&cfid);
	if(cfid!=101 && cfid!=102){
		printf("Entered invalid flight number\n");
		return 0;
	}
	cfid-=101;
	printf("Economy class : %d and Business class : %d\n",f[cfid].b_ep,f[cfid].b_bp);
	printf("Enter class (B/E) : ");
	fflush(stdin);
	scanf("%c",&ct);
	if(ct=='B' || ct=='b'){
		avs=f[cfid].bt-f[cfid].bb;
		b[b_i].type='B';
		printf("Number of seats available : %d\n",avs);	
		printf("Enter number of Seats to be booked : ");
		scanf("%d",&cns);
		while(cns>avs){
			printf("Number of seats available : %d\n",avs);	
			printf("Enter number of Seats to be booked : ");
			scanf("%d",&cns);
		}
		printf("Want to proceed to book (Y/N): ");
		fflush(stdin);
		scanf("%c",&qt);
		if(qt=='N' || qt=='n'){
			return 0;
		}
		printf("Booking ..\n");
		b[b_i].ns=cns;          //
		f[cfid].bb+=cns;
		printf("Meal cost per seat 200.\n");
		printf("Do you want meals provision  (Y/N) : ");
		fflush(stdin);
		scanf("%c",&qt);
		if(qt=='Y' || qt=='y'){
			mf=1;
			b[b_i].mcond=1;

		}
		else{
			mf=0;
			b[b_i].mcond=0;
		}
		i=0;
		for(;i<6;i++){
			if(f[cfid].bok[i]==0){
				b[b_i].seats[i]=1;
				if(mf>0)
					f[cfid].m[i]=1;
				cns--;
				f[cfid].bok[i]=1;
				if(cns==0)
					break;
			}
		}
//		f[cfid].totalb[f[cfid].totalb_i]=b_i;     ******
		f[cfid].totalb_i+=1;
		b[b_i].cost=b[b_i].ns*(f[cfid].b_bp+f[cfid].surgep*b[b_i].mcond);
		f[cfid].s_bp+=1;
		f[cfid].b_bp+=f[cfid].surgep; // Surfe pricing
		printf("Cost of booking : %d\n",b[b_i].cost);
	}
	else if(ct=='E' || ct=='e'){
		b[b_i].type='E';
		avs=f[cfid].et-f[cfid].eb;
		printf("Number of seats available : %d\n",avs);
		printf("Enter number of Seats to be booked : ");
		scanf("%d",&cns);
		while(cns>avs){
			printf("Number of seats available : %d\n",avs);	
			printf("Enter number of Seats to be booked : ");
			scanf("%d",&cns);
		}
		printf("Want to proceed to book (Y/N): ");
		fflush(stdin);
		scanf("%c",&qt);
		if(qt=='N' || qt=='n'){
			return 0;
		}
		printf("Booking ..\n");
		b[b_i].ns=cns;   
		f[cfid].eb+=cns;
		printf("Meal cost per seat 200.\n");
		printf("Do you want meals provision  (Y/N) : ");
		fflush(stdin);
		scanf("%c",&qt);
		if(qt=='Y' || qt=='y'){
			mf=1;
			b[b_i].mcond=1;
		}
		else{
			mf=0;
			b[b_i].mcond=0;
		}
		i=6;
		for(;i<18;i++){
			if(f[cfid].bok[i]==0){
				b[b_i].seats[i]=1;
				if(mf>0)
					f[cfid].m[i]=1;
				cns--;
				f[cfid].bok[i]=1;
				if(cns==0)
					break;
			}
		}
//		f[cfid].totalb[f[cfid].totalb_i]=b_i;        *******
		f[cfid].totalb_i+=1;
		b[b_i].cost=(b[b_i].ns)*(f[cfid].b_ep+f[cfid].surgep*b[b_i].mcond);   // surging base price == meals price both are 200 and both are constants ie not modifed in program
		f[cfid].s_ep+=1;
		f[cfid].b_ep+=f[cfid].surgep; // Surfe pricing
		printf("Cost of booking : %d\n",b[b_i].cost);
	}
	else{
		printf("Entered invalid class\n");
		return 0;
	}
	printf("\nBooking ID : %d\n",b_i+1);
	printf("Booking created successfully\n");	
	b[b_i].bid=b_i;  // booking id
	b[b_i].fid=cfid+101;
	b[b_i].condition=1;
	b_i++;
	f[cfid].tcost+=b[b_i].cost;
	return 1;
}

int cancel(){
	int i,nos;
	int cfid,cbid;
	printf("Enter booking id : \n");
	scanf("%d",&cbid);
	if(cbid>b_i || cbid<1){
		printf("Entered invalid booking Id\n");
		return 0;
	}
	cbid-=1;
	if(b[cbid].type=='e' || b[cbid].type=='E'){
		f[cfid].eb-=(b[cbid].ns);
	} 
	else{
		f[cfid].bb-=(b[cbid].ns);		
	}
	b[cbid].condition=0;
	cfid=b[cbid].fid-101;
	nos=b[cbid].ns;
	f[cfid].tcost-=(0.8*b[cbid].cost);
	for(i=0;i<18;i++){
		if(b[cbid].seats[i]){
			f[cfid].bok[i]=0;
			f[cfid].m[i]=0;
			b[cbid].seats[i]=0;
			nos--;
		}
		if(nos==0)
			break;
	}
	printf("\nCancellation charge : %d\n",(int)b[cbid].cost/5);
	printf("Booking Cancelled Successfully");
	return 1;
}

void printallb(){
	int i=0;
	for(i=0;i<b_i;i++){
		if(b[i].condition==1){
			printf("\nBooking ID : %d\n",i+1);
			printf("Flight Id : %d\n",b[i].fid);
			printf("Number of seats booked : %d\n",b[i].ns);
			printf("Type of class booked : %c\n",b[i].type);
			if(b[i].mcond==1)
				printf("Meal provided\n");
			else
				printf("Not opted for meals\n");
			printf("Booking cost : %d\n",b[i].cost);
		}
		else{
			printf("Booking cancelled : %d",i);
		}
	}
	return;
}

int psavail(){
	int cfid,avs;
	char ct;
	printf("Enter flight Number : ");
	scanf("%d",&cfid);
	if(cfid!=101 && cfid!=102){
		printf("Entered invalid flight number\n");
		return 0;
	}
	cfid-=101;
	printf("Enter class (B/E) : ");
	fflush(stdin);
	scanf("%c",&ct);
	if(ct=='B' || ct=='b'){
		avs=f[cfid].bt-f[cfid].bb;
		printf("Number of seats available : %d",avs);
	}
	else if(ct=='E' || ct=='e'){
		avs=f[cfid].et-f[cfid].eb;
		printf("Number of seats available : %d",avs);
	}
	else{
		printf("Entered Invalid class\n");
		return 0;
	}
	return 1;
}

int psnumformeal(){
	int cfid,i,c=0;
//	char ct;
	printf("Enter flight Number : ");
	scanf("%d",&cfid);
	if(cfid!=101 && cfid!=102){
		printf("Entered invalid flight number\n");
		return 0;
	}
	cfid-=101;
//	printf("Enter class (B/E) : ");
//	fflush(stdin);
//	scanf("%c",&ct);
//	if(ct=='B' || ct=='b'){
		printf("Seat numbers who ordered for meals : \n");
		i=0;
/*		for(;i<6;i++){
			if(f[cfid].m[i]==1){
				printf("%d ",i+1);
				c++;
			}
		}   */
//	}
//	else if(ct=='E' || ct=='e'){
//		printf("Seat numbers who ordered for meals : \n");
//		i=6;
		for(;i<18;i++){
			if(f[cfid].m[i]==1){
				printf("%d ",i+1);
				c++;
			}
		}
		if(c==0)
			printf("Nill\n");
		else
			c=0;
//	}
/*	else{
		printf("Entered Invalid class\n");
		return 0;
	}   */
	return 1;
}

int flightboksum(){
	int cfid,i=0;
	printf("Enter flight number : ");
	scanf("%d",&cfid);
	if(cfid!=101 && cfid!=102){
		printf("Entered Invalid option.\n");
		return 0;
	}
	cfid-=101;
	printf("-------  Flight Summary  --------\n");
	printf("Total number of booking : %d\n",f[cfid].totalb_i);
	printf("Number of economy class seats booked : %d\n",f[cfid].eb);
	printf("Number of business class seats booked : %d\n",f[cfid].bb);
	printf("Seats not booked : \n");
	for(i=0;i<18;i++){
		if(f[cfid].bok[i]==0){
			printf("%d ",i+1);
		}
	}
	printf("\nSeat numbers booked : \n");
	for(i=0;i<18;i++){
		if(f[cfid].bok[i]>0){
			printf("%d ",i+1);
		}
	}
	printf("\nSeats number who ordered for meals : \n");
		for(i=0;i<18;i++){
		if(f[cfid].m[i]>0){
			printf("%d ",i+1);
		}
	}
	printf("\nTotal cost : %d\n",f[cfid].tcost);
	return 1;
}

int main(){
	int i=0,f=1,op,k,fb=0;
	init();
//	return 0;
	printf(" -- Flight booking system -- \n");
	while(f){
		printf("\n1.Booking\n2.Cancelling\n3.Print available seats\n4.Print seat numbers who oredered meals\n5.Print individual file Booking Summary\n6.Print all Booking\n7.Logout\n");
		printf("Enter a valid option : ");
		scanf("%d",&op);
		while(op>7){
			printf("Enter a valid option : ");
			scanf("%d",&op);
		}
		switch(op){
			case 1 :{
				k=book();
				fb=1;
				if(k){
					printf("Booking Successful\n");
				}
				else{
					printf("Booking Failed\n");
				}
				break;
			}
			case 2:{
				fb=0;
				if(b_i==0)
					goto xy;
				k=cancel();
				if(k){
					printf("\nOperation Successful\n");
				}
				else{
					printf("Operation Failed. Try Again\n");
				}
				break;
			}
			case 3:{
				fb=0;
				if(b_i==0)
					goto xy;
				k=psavail();
				if(k){
					printf("\nOperation Successful\n");
				}
				else{
					printf("Operation Failed. Try Again\n");
				}
				break;
			}
			case 4:{
				fb=0;
				if(b_i==0)
					goto xy;
				k=psnumformeal();
				if(k){
					printf("\nOperation Successful\n");
				}
				else{
					printf("Operation Failed. Try Again\n");
				}
				break;
			}
			case 5 : {
				fb=0;
				if(b_i==0)
					goto xy;
				k=flightboksum();
				if(k){
					printf("\nOperation Successful\n");
				}
				else{
					printf("Operation Failed. Try Again\n");
				}
				break;
			}
			case 6:{
				fb=0;
				if(b_i==0)
					goto xy;
				printallb();
				printf("Operation Successful");
				break;
			}
			case 7:{
				f=0;
				fb=0;
				printf("Logging you out ...");
				break;
			}
			default : {
				printf("Entered wrong option\n");
				break;
			}
		}
		if(b_i==0 && fb==0){
			xy:
			printf("No bookings found.\n");
		}
	}
	return 0;
}