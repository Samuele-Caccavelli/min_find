#include "Parameters.hpp"

// void print_point(const Vector & x) {
//   for(auto component : x) {
//     std::cout << component << "\t";
//   }
//   std::cout << "\n";
// }

// std::ostream &
// operator<<(std::ostream &out, const Parameters &p)
// {
//   out << "PARAMETER VALUES:"
//       << "\n";
//   out << "dim = " << p.dim << "\n";
//   // out << "init_cond = ";
//   // print_point(p.init_cond);
//   out << "tol_step= " << p.tol_step << "\n";
//   out << "tol_res= " << p.tol_res << "\n";
//   out << "mu= " << p.mu << "\n";
//   out << "sigma= " << p.sigma << "\n";
//   out << "alpha_0= " << p.alpha_0 << "\n";
//   out << "max_iter= " << p.max_iter << "\n\n";
//   return out;
// }