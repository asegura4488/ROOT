void Hypothesis(){

HMethods *M = new HMethods();
//M->SetConfig("ISRconfig");
M->SetConfig("config");
M->Init("signal");
M->InitXsec("xsec");
//M->Show();
M->InitWorkspaces("combined");
M->CreateModels("obsData", "ModelConfig");
// like = likelihood , frequentist = frequentist ,profile = profilebinnedlikelihood, Hybrid = hybrid method, asym = asymtotic method ,Markov = Markov MC method
M->GetHypoTest(0,"Hybrid"); // -1 for all signal point, another value for the index of signal in the vecr
M->PlotLimit(true);

}

