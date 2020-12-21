void run(){
 
 gROOT->ProcessLine(".L ModelInspector.C");  
 //gROOT->ProcessLine("ModelInspector(\"../workspaces/chargino100_stau_75_lsp50.root\", \"combined\", \"ModelConfig\", \"obsData\")");
 gROOT->ProcessLine("ModelInspector(\"../workspaces/chargino100_stau75_lsp50.root\", \"combined\", \"ModelConfig\", \"obsData\")");
 //gROOT->ProcessLine("ModelInspector(\"../workspaces/chargino100_stau75_lsp50_o.root\", \"combined\", \"ModelConfig\", \"obsData\")");

}

int main(){
run();
return 0;
}
