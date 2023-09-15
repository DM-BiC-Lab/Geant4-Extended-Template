#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

void process_data(int num) {
    string fileNumber = to_string(num);
    ifstream data_file;
    data_file.open("../output_" + fileNumber + "_nt_Hits.csv");
    if (!data_file.is_open()) {
        cout << "Unable to process data. Input data file not found.\n";
        return;
    }
    
    ifstream variable_file;
    variable_file.open("../../project-variables.txt");
    if (!variable_file.is_open()) {
        cout << "Unable to process data. Project variable file not found.\n";
        return;
    }
    
    TFile *root_file = new TFile("output.root", "RECREATE");
    
    ofstream text_file;
    text_file.open("formatted.txt");
    
    TH1F *x_hist = new TH1F("X Hits", "X Hits", 40, -200, 200);
    TH1F *y_hist = new TH1F("Y Hits", "Y Hits", 40, -200, 200);
    TH1F *z_hist = new TH1F("Z Hits", "Z Hits", 100, -375, 625);
    
    TH1F *trail_hist = new TH1F("Hits Per Trail", "Hits Per Trail", 200, -0.5, 200.5);
    
    string line;
    int current_run = -1;
    while (getline(data_file, line)) {
        if (line.at(0) == '#') { continue; }
        
        vector<string> tokens;
        int last_split = 0;
        for (int i = 0; i < line.length(); i++) {
            if (line.at(i) == ',') {
                tokens.push_back(line.substr(last_split, i - last_split));
                last_split = i + 1;
            }
        }
        tokens.push_back(line.substr(last_split, line.length() - last_split));
        
        for (int i = 0; i < tokens.size(); i++) {
            float value = stoi(tokens.at(i));
            switch (i) {
                case 0:
                    trail_hist->Fill(value + 1);
                    break;
                case 1:
                    x_hist->Fill(value);
                    break;
                case 2:
                    y_hist->Fill(value);
                    break;
                case 3:
                    z_hist->Fill(value);
                    break;
            }
            
            if (i == 0 && value != current_run) {
                current_run++;
                if (current_run > 0) { text_file << "\n\n"; }
                text_file << "Run #" + to_string(int(value) + 1) + ":\n";
            } else if (i != 0) {
                text_file << right << setw(8) << tokens.at(i);
                if (i == 3) { text_file << '\n'; }
            }
        }
    }
    
    trail_hist->GetXaxis()->SetRange(0, current_run + 3);
    
    root_file->Write();
    root_file->Close();
    text_file.close();	
}
