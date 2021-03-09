void Confidence(){

   	//Methods *test1 = new Methods(2000.,1900.,300.);
   	Methods *test1 = new Methods(10.,8.,15.);
   // Methods *test1 = new Methods(147., 140., 58.);
   //  Methods *test1 = new Methods(400.,400.,100.);
   //  Methods *test1 = new Methods(300.,290.,60.);

   // test1->GetExpected();
     test1->SetNtoys(1E+6);

   // Double_t limit_ = test1->GetLimit(0.95, 1);
   // cout << limit_ << " " << limit_/test1->GetNsignal() << endl;

    Double_t limit_ = 0.;
/*    limit_ = test1->GetLimit(0.95, 2);
	  cout << " limit " << limit_ << " " << limit_/test1->GetNsignal() << endl;
*/
   // limit_ = test1->GetLimit(0.95, 4, 0.1);

     limit_ = test1->GetLimit(0.95, 4 , 0.5);
    
    cout << " limit2 " << limit_ << " " << limit_*test1->GetNsignal() << endl;
  
 //   limit_ = test1->GetFrequestistqm(0.6,1E+5, 5);



   // limit_ = test1->GetLimit(0.95, 3);
/*
    Methods *test2 = new Methods(7.,7.,16.);
    Double_t limit2_ = test2->GetLimit(0.95, 2);
//    cout << limit2_ << " " << limit2_/test2->GetNsignal() << endl;


    Double_t epsilon = 1E-6;
    Double_t counter = 0.;
 	Double_t mu = 0.;
    Double_t limit = 0.;

    Double_t CL = 0.05;

    while(TMath::Abs(limit - CL) > epsilon){
   	    counter += epsilon;
        mu = counter;
    	limit = test1->GetFrequestistCls(mu)*test2->GetFrequestistCls(mu);
    	//cout << mu << " " << limit << " " << test1->GetFrequestistCls(mu) << " " <<  test2->GetFrequestistCls(mu) << endl;
	}
*/
//	cout << mu << " " << mu/(test1->GetNsignal()+test2->GetNsignal()) <<endl; 

}

int main(){

	Confidence();
	return 0;

}
