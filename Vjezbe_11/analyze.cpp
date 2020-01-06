#include<Analyzer.h>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>


using namespace std;

int main(){
	srand (time(NULL));
	Analyzer *a = new Analyzer();
	//cout<<a->CPUpper(2,0.6827,10)<<endl;
	//cout<<a->Binomial(3,0.001,10)<<endl;
	
	//cout<<a->CPLower(2,0.6827,10)<<endl;
	a->ClopperPearson(10,0.6827);
	a->Show();
	/*int i=0, br, br2=0;
	int t;
	while(i<1000){
	br=0;
		for(int j=0;j<10;j++){
			t=rand()%6+1;
			if(t==6){
				br++;
			}
		}
		
		if(br==0){
			br2++;
		
		}
		else{
		if(1.0/6.0 > a->CPLower(br, 0.90,10) && 1.0/6.0 < a->CPUpper(br, 0.9,10)){
			br2++;
		}
		
		}
		
		
 		i++;
	}
	cout<<br2/10.0<<"%"<<endl;*/
	
	
	
	return 0;
}
