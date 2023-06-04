#include <iostream>
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include "load/load.h"
#include "algebra/alg.h"
#include "ia/layers/actlayer.h"
#include "ia/layers/fclayer.h"
#include "ia/network/network.h"
#include "funcs/functions.h"


using namespace std;

int get_maximum_index(alg::Matrix& y_pred) {
    int res = 0;
    auto val = y_pred.get_val(0,0);
    for (int i=1; i<y_pred.get_cols(); i++) {
        auto new_val = y_pred.get_val(0,i);
        if (new_val > val) {
            res = i;
            val = new_val;
        }
    }
    return res;
}

int main() {
    /*
    alg::::vec_mat x_train = { 
        alg::Matrix( alg::t_mat{ {1,1}} ),
        alg::Matrix( alg::t_mat{ {0,0}} ),
        alg::Matrix( alg::t_mat{ {0,1}} ),
        alg::Matrix( alg::t_mat{ {1,0}} ),
    };

    alg::::vec_mat y_train = {
        alg::Matrix( alg::t_mat{ {0}} ),
        alg::Matrix( alg::t_mat{ {0}} ),
        alg::Matrix( alg::t_mat{ {1}} ),
        alg::Matrix( alg::t_mat{ {1}} ),
    };
    */


    cout << "Init Layers" << endl;
    ai::ptr_layer fc1  = std::make_shared<ai::FCLayer>(4.0,8.0);
    ai::ptr_layer act1 = std::make_shared<ai::ActLayer>(8.0, hypertan, hypertan_drv); //relu, relu_drv);
    ai::ptr_layer fc2  = std::make_shared<ai::FCLayer>(8.0,5.0);
    ai::ptr_layer act2 = std::make_shared<ai::ActLayer>(5.0, hypertan, hypertan_drv); // relu, relu_drv);
    ai::ptr_layer fc3  = std::make_shared<ai::FCLayer>(5.0,3.0);
    ai::ptr_layer act3 = std::make_shared<ai::ActLayer>(3.0, hypertan, hypertan_drv); // relu, relu_drv);
    cout << "End Layers" << endl;

    
    auto nw = ai::Network(mse, mse_drv);
    nw.add_layer(fc1);
    nw.add_layer(act1);
    nw.add_layer(fc2);
    nw.add_layer(act2);
    nw.add_layer(fc3);
    nw.add_layer(act3);


    auto x_train = load_file("datasets/x.csv");
    auto y_train = load_file("datasets/y.csv");
    /*
    ifstream XFile("datasets/x.csv");
    ifstream YFile("datasets/y.csv");

    string line;
    string num;
    char delim = ' '; 

    alg::vec_mat x_train{};
    while (std::getline(XFile, line)) {
        std::stringstream ss(line);
        alg::t_row tmp_row{};
        while (std::getline(ss, num, delim)) {
            tmp_row.push_back( std::stod(num) );
        }
        x_train.push_back(alg::Matrix{{tmp_row}});
    }

    alg::vec_mat y_train{};
    while (std::getline(YFile, line)) {
        std::stringstream ss(line);
        alg::t_row tmp_row{};
        while (std::getline(ss, num, delim)) {
            tmp_row.push_back( std::stod(num) );
        }
        y_train.push_back(alg::Matrix{{tmp_row}});
    }
    */


    std::cout << "INIT WEIGHTS OF L0" << endl;
    std::dynamic_pointer_cast<ai::FCLayer> (fc1) -> get_weights().display();
    //nw.predict( x_train[0] ).display();
    std::cout << "TRAIN" << endl;
    nw.fit(x_train,y_train,1000,0.01);
    std::cout << "FINAL WEIGHTS OF L0" << endl;
    std::dynamic_pointer_cast<ai::FCLayer> (fc1) -> 
    get_weights().display();
    

    vector<double> misses(3);
    vector<double> total(3);
    auto res = nw.predict(x_train);
    for (int ind = 0; ind < res.size(); ind ++) {
        auto real = get_maximum_index( y_train[ind] );
        if ( real != get_maximum_index( res[ind] ) ) {
            misses[real] += 1;            
        }
        total[real] += 1;
    }
    cout << "Misses:" << endl;
    for (int i=0; i<3; i++) {
        cout << misses[i] / total[i] <<  std::endl;
    } 

    /*
    vector<double> misses(3);
    vector<double> total(3);
    for (int ind = 0; ind < x_train.size(); ind ++) {
        auto tmp = nw.predict(x_train[ind]);
        auto real = get_maximum_index( y_train[ind] );
        if ( real != get_maximum_index( tmp ) ) {
            misses[real] += 1;            
        }
        total[real] += 1;
    }
    cout << "Misses:" << endl;
    for (int i=0; i<3; i++) {
        cout << misses[i] / total[i] <<  std::endl;
    } 
    */

    
    //nw.predict(X).display();
    /*
    auto a = alg::Matrix( alg::t_mat{ {1,2,3}} );
    auto b = alg::Matrix( alg::t_mat{{-5,2},{-4,4},{-3,1}});
    auto c = alg::Matrix( alg::t_mat{{1},{2}});
    cout << "INPUT" << endl;
    a.display();
    cout << "WEIGHTS" << endl;
    b.display();

    // Create Network
    auto nw = ai::Network(mse, mse_drv);

    // Add layers
    std::shared_ptr<ai::BaseLayer> fc1 = std::make_shared<ai::FCLayer>(3.0,2.0);
    std::shared_ptr<ai::BaseLayer> act1 = std::make_shared<ai::ActLayer>(3.0, relu, relu_drv);
    std::shared_ptr<ai::BaseLayer> fc2 = std::make_shared<ai::FCLayer>(2.0,1.0);
    std::dynamic_pointer_cast<ai::FCLayer> (fc1) ->set_weights(b);
    std::dynamic_pointer_cast<ai::FCLayer> (fc2) ->set_weights(c);
    nw.add_layer(fc1);
    nw.add_layer(act1);
    nw.add_layer(fc2);

    // Predict
    auto r = nw.predict(a);
    cout << "RESULTS" << endl;
    r.display();
    return 0;
    */
}