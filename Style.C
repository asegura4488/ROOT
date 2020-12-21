
void SetStyle(){

	gStyle->SetOptStat(0); // No stats
	gStyle->SetOptTitle(0); // No title


	// X and Y axis	
	gStyle->SetTitleSize(0.05,"x");
	gStyle->SetTitleSize(0.05,"y");

	gStyle->SetLabelSize(0.03,"x");
	gStyle->SetLabelSize(0.03,"y");


	// Change the margins 

	gStyle->SetPadTopMargin(0.05);
	gStyle->SetPadBottomMargin(0.15);
	gStyle->SetPadLeftMargin(0.1);
	gStyle->SetPadRightMargin(0.05);

}


void Style(){


	SetStyle();

	TH1D *h1 = new TH1D("h1","h1",50,0.,1.);
	h1->GetXaxis()->SetTitle("m_{T}(#mu, E_{T}^{miss})");
	h1->GetYaxis()->SetTitle("Events");

	h1->Draw();

	return 0;
}