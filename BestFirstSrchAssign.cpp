#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>adj_matrix(28, vector<int>(28, 0));

int Convert_to_Index(char c)
{
    if(c == '.')
    return 26;

    else if(c == ' ')
    return 27;

    return c - 'a';
}

char Convert_to_Char(int n)
{   if(n == 26)
    return '.';

    else if(n == 27)
    return ' ';

    return 'a' + n;
}

void BuildGraph(string s)
{
 int prev_idx = -1;   
 for(auto ch : s)
 {   
  ch = tolower(ch);
  int curr_idx = Convert_to_Index(ch);
  if (prev_idx != -1) 
  {
    adj_matrix[prev_idx][curr_idx]++;
  }
  prev_idx = curr_idx;
 }
}
string FileRead(string file_name)
{
   ifstream file(file_name);
   string result;
   if (!file.is_open()) 
   {          
        cout << "Failed to open the file." << endl;
   }
   string line;
   while(getline(file,line))
   {
      result += line;  
   }
   return result;
}

string Enhance(string str)
{
   char s;
   string result;   

   for(auto c : str)
   {
      if(c == '.' || c == ' ' || isalpha(c))
      {
        result += c;
      }
   }
   return result;
}

void Display_Matrix()
{
    int width = 4;
    cout<<"Adjacency Matrix:\n";
    cout<<" ";
    for(int i = 0 ;  i < 28 ; i++)
    {
        cout<<setw(width)<<Convert_to_Char(i);
    }
    cout<<endl;
    for (int i = 0; i < 28; i++) {
cout << Convert_to_Char(i) << " ";
for (int j = 0; j < 28; j++) {
    cout << setw(width) << adj_matrix[i][j];
}
cout << endl;
}
cout << endl;
};
string best_first_search(vector<vector<int>>&adj_matrix) {
    int n = adj_matrix.size();
    queue<int> q;
    vector<int> vis(n, 0);
    string output = "";
    char start_char;
    
    cout << "Enter the starting character: ";
    cin >> start_char;
    
    if (!(start_char == ' ' || start_char == '.' || ('a' <= start_char && start_char <= 'z'))) {
        cout << "INVALID STARTING CHARACTER.\n";
        return output;
    }
    
    int start_index = Convert_to_Index(start_char);
    q.push(start_index);
    vis[start_index] = 1;

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        char ch = Convert_to_Char(vertex);
        output += ch; 
        if(ch == '.')
        return output;

        int maxi_freq = -1e9;
        int at_index = -1;
        for (int i = 0; i < n; i++) {
            if (!vis[i] && adj_matrix[vertex][i] != 0) {
                if (maxi_freq < adj_matrix[vertex][i]) {
                    maxi_freq = adj_matrix[vertex][i];
                    at_index = i;
                }
            }
        }
        if (at_index != -1) {
            q.push(at_index);
            vis[at_index] = 1; 
        }
    }
    return output;
}

int main()
{
    string refined_string = Enhance(FileRead("BFS_file.txt"));
    BuildGraph(refined_string);
    Display_Matrix();
    string output = best_first_search(adj_matrix);
    cout<<output<<endl;
    return 0;
}

