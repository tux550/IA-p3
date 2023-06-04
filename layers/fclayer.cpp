#include <random>
#include <iostream>
#include "./fclayer.h"

namespace ai{
    // Constructor
    FCLayer::FCLayer(alg::t_dim inp_size, alg::t_dim out_size):
        BaseLayer{inp_size,out_size},
        weights_mat{ {inp_size, out_size} },
        bias{ {1, out_size} }
        {
            // Generate random number generator
            alg::t_type lower_bound = 0;
            alg::t_type upper_bound = 1;
            std::uniform_real_distribution<alg::t_type> unif(lower_bound, upper_bound);
            std::default_random_engine re;
            // Generate random weights
            for (alg::t_dim r=0; r<inp_size; r++) {
                for (alg::t_dim c=0; c<out_size; c++) {
                    auto val = unif(re);
                    weights_mat.set_val({r,c},val);
                }
            }
            // Generate random bias
            for (alg::t_dim c=0; c<out_size; c++) {
                auto val = unif(re);
                bias.set_val({0,c},val);
            }
        }
    // Forward Propagation
    alg::MultidimMatrix FCLayer::forward_propagation_implementation(alg::MultidimMatrix &im) {
        return alg::mat_prod(im, weights_mat)+bias;
    }
    // Backward Propagation
    alg::MultidimMatrix FCLayer::backward_propagation(alg::MultidimMatrix &out_error, alg::t_type alpha) {
        // TODO
        
        // Calc error
        auto wt = weights_mat.transpose();
        auto in_error = alg::mat_prod(out_error, wt);
        auto input_data_t = input_data.transpose();
        auto we_error = alg::mat_prod(input_data_t, out_error);

        std::cout << "OUT_ERROR" << std::endl;
        out_error.display();
        std::cout << "wt" << std::endl;
        wt.display();
        std::cout << "in_error" << std::endl;
        in_error.display();
        std::cout << "input_data_t" << std::endl;
        input_data_t.display();
        std::cout << "we_error" << std::endl;
        we_error.display();
        throw;

        // Update
        weights_mat = weights_mat - (we_error * alpha);
        bias        = bias - (out_error * alpha);

        // Return error
        return in_error;
    }
    // Setters
    void FCLayer::set_weights(alg::MultidimMatrix &w) {
        weights_mat = w;
    }
    // Getters
    alg::MultidimMatrix FCLayer::get_weights() {
        return weights_mat;
    }
}
