#include<iostream> 
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;

double cost_function(vector<double> &x,vector<double> &y,double w,double b){
    int m=x.size();
    double J=0;
    for(int i=0;i<m;i++){
        J+=(w*x[i]+b-y[i])*(w*x[i]+b-y[i]);
    }
    J= J/(2*m);
    return J;
}

void print_learning_curve(vector<pair<double,double>>& learning_curve){

    for(int i=0;i<learning_curve.size();i++){
        cout<<learning_curve[i].second<<"->"<<learning_curve[i].first<<'\n';
    }

}

pair<double,double> calc_gradient(vector<double>& x,vector<double>& y,double w,double b){

    int m=x.size();

    double dj_dw=0;
    double dj_db=0;

    for(int i=0;i<m;i++){

        dj_db=dj_db+(w*x[i]+b-y[i]);
        dj_dw=dj_dw+(w*x[i]+b-y[i])*x[i];

    }
    dj_dw=dj_dw/m;
    dj_db=dj_db/m;

    return {dj_dw,dj_db};
}

pair<double,double> gradient_descent(vector<double>& x,vector<double>& y,double w,double b,double alpha,int n_iters,vector<pair<double,double>> &learning_curve){

    for(int i=0;i<n_iters;i++){

        pair<double,double> gradients=calc_gradient(x,y,w,b);
        double dj_dw=gradients.first;
        double dj_db=gradients.second;

        learning_curve.push_back({cost_function(x,y,w,b),i});

        w=w-alpha*dj_dw;
        b=b-alpha*dj_db;

    }
    return{w,b};
}

void load_data(string fileName,vector<double>& x,vector<double>& y){

    ifstream data(fileName);
    string row;

    // Skip the label row
    getline(data,row);

    // Read the data row by row
    while (getline(data,row)) {

        stringstream s(row);
        string val;

        //skip the indexing
        //a modification to load_data function can be made to skip indexing if present
        //or you can just comment this line out if no indexing in csv data
        getline(s,val,',');

        //read first column value (x)
        getline(s,val,',');
        x.push_back(stod(val));

        //read second column value (y)
        getline(s,val,',');
        y.push_back(stod(val));

    }

    data.close();
}

double lr_predict(double input,double weight,double bias){
    return weight*input+bias;
}

int main(){

    vector<double> x;
    vector<double> y;

    load_data("data.csv",x,y);

    //learning rate
    double alpha=0.001;
    //number of iterations
    double n_iters=1000;

    vector<pair<double,double>> learning_curve;

    double w_initial=10000;
    double b_initial=500;

    pair<double,double> parameters=gradient_descent(x,y,w_initial,b_initial,alpha,n_iters,learning_curve);

    double weight = parameters.first;
    double bias = parameters.second;

    double input;
    cin>>input;

    //line below can be used to see the variation of cost_function w.r.t. number of iteration
    // print_learning_curve(learning_curve);

    double prediction = lr_predict(input,weight,bias);

    cout<<"prediction: "<<prediction<<'\n';

    return 0;
}
