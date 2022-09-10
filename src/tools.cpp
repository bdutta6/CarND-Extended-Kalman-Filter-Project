#include "tools.h"
#include <iostream>

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;
using std::cout;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
   * TODO: Calculate the RMSE here.
   */

  VectorXd rmse_vector(0,0,0,0);

  //Check for the estimations and ground truth vector and ensure its non empty

  if(estimations.size() == 0) {
   cout << "CalculateRMSE: The estimations vector is empty " <endl;
   return rmse_vector;
  }

  if(ground_truth.size() == 0) {
   cout << "CalculateRMSE: The ground truth vector is empty " <endl;
   return rmse_vector;
  }

  //Check to ensure that the estimation vector and the ground truth vector are of the same size

  if(estimations.size()!=ground_truth.size()){
   cout << "CalculateRMSE: The estimation vector and the ground truth vector are not of equal lengths " <endl;
   return rmse_vector;
  }

  //Calculate the mean square error between the ground truth and the estimation vector

  for(int sample_count =0; sample_count< estimations.size(); ++sample_count){
   VectorXd difference_by_sample =estimations[i]-ground_truth[i];
   difference_by_sample=difference_by_sample.array()*difference_by_sample.array();
   rmse_vector= rmse_vector+difference_by_sample;
  }

  rmse_vector= rmse_vector/estimations.size();
  rmse_vector=rmse_vector.array().sqrt();


}

MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
  /**
   * TODO:
   * Calculate a Jacobian here.
   */

  MatrixXd Jacobian (3,4);

  // Check for the size of the state vector

  if(x_state.size() !=4){
   cout << "CalculateRMSE: The state vector dimension does not match" <endl;
   return Jacobian;
  } 

  	//extract state parameters
	double px = x_state(0);
	double py = x_state(1);
	double vx = x_state(2);
	double vy = x_state(3);

   // Compute the Jacobian matrix components
   
   double temp = px*px+py*py;
   double elem1= px/sqrt(temp);
   double elem2= py/sqrt(temp);
   double elem3= py/temp;
   double elem4= px/temp;

   double elem5= (py*(vx*py-vy*px))/(temp*sqrt(temp));
   double elem6= (px*(vy*px-vx*py))/(temp*sqrt(temp));

   Jacobian << (elem1, elem2, 0, 0,
                  -elem3, elem4, 0, 0,
                     elem5, elem6, elem1, elem2);

   return Jacobian;                  


}
