void run(int a=0){

 if(a==0){ 
 gROOT->ProcessLine(".L StandardHypoTestInvDemo.C");
 gROOT->ProcessLine("StandardHypoTestInvDemo(\"../workspaces/chargino200_stau_185_lsp170.root\", \"combined\", \"ModelConfig\",\"\", \"obsData\", 2, false)");
 } 
 else if(a==1){
 gROOT->ProcessLine(".L StandardHypoTestDemo.C");
 gROOT->ProcessLine("StandardHypoTestDemo(\"../workspaces/chargino200_stau_185_lsp170.root\", \"combined\", \"ModelConfig\",\"\", \"obsData\", 0, false)");
 } 
 else if(a==2){
 gROOT->ProcessLine(".L aguilar/StandardHypoTestDemo.C");
 gROOT->ProcessLine("StandardHypoTestDemo(\"../workspaces/chargino200_stau_185_lsp170.root\", \"combined\", \"ModelConfig\",\"\", \"obsData\", 0, false)");
 }


}

int main(){
run(0);
return 0;
}
