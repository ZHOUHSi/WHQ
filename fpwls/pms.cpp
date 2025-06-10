#include "basis_pms.h"
#include "build.h"
#include "pms.h"
#include "heuristic.h"
#include <signal.h>


Satlike s;
void interrupt(int sig)
{
	s.print_best_solution();
	s.free_memory();
	exit(10);
}

int main(int argc, char *argv[])
{
	start_timing();

	signal(SIGTERM, interrupt);

	s.build_instance(argv[1]);

	if (argc > 2) {
        int user_cutoff = atoi(argv[2]); // 将字符串转换为整数
        if (user_cutoff > 0) {
            cutoff = user_cutoff; // 将用户输入的值赋给全局变量 cutoff_time
            std::cout << "Cutoff time set to: " << cutoff << " seconds" << std::endl;
        } else {
            std::cerr << "Invalid cutoff time. Please provide a positive integer." << std::endl;
            return 1; // 错误退出
        }
    } else {
        std::cout << "Using default cutoff time: " << cutoff << " seconds" << std::endl;
    }

	s.settings();

	s.local_search_with_decimation(argv[1]);

	s.simple_print();

	s.free_memory();

	return 0;
}
