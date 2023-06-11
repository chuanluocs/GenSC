# GenSC -- A Novel and General Local Search Framework for Set Covering Problem (SCP)

GenSC is a highly configurable framework, which integrates many effective techniques. After automatic configuration, GenSC can instantiate effective local search algorithms that exhibits high performance on solving different types of SCP instances. Extensive experiments on various application SCP instances demonstrate that GenSC performs much better than previous algorithms, indicating that GenSC advances the state of the art in SCP solving.

## Author and Implementer
- Chuan Luo (<chuanluo@buaa.edu.cn>)
- Taoyu Chen (<20231207@buaa.edu.cn>)

## LICENSE
- This project is licensed under the terms of the GPLv3 license.

## Benchmarks

- All the benchmarks can be found in the directory entitled `Benchmarks`, including `OR-Large`, `OR-Small`, `Rail`, `SCP-CLR`, `SCP-CYC`, `STS`, `SoftTest-L`, `SoftTest-M`, `SoftTest-S`. Their sizes are summarized in `benchmark_sizes.csv`.

- In our paper, we used SMAC for GenSC's configuration tuning. For each benchmark, we used the following instances as training sets:

|     Benchmark    |            Training Set           |
|:----------------:|:---------------------------------:|
|        Rail      |   rail-507, rail-2536, rail-4284  |
|      SCP-CLR     |        scpclr-10, scpclr-12       |
|      SCP-CYC     |   scpcyc-6, scpcyc-8, scpcyc-10   |
|        STS       |          sts-135, sts-405         |
|    SoftTest-S    |           Apache, x264            |
|    SoftTest-M    |            BDBC, Dune             |
|    SoftTest-L    |                sac                |

## Source Codes of GenSC

- The source codes of GenSC can be found in the directory entitled `Code`.

## Build GenSC
To build GenSC, please run the following command:
```shell
cd Code && make
```

## Run GenSC

>**Quick Start**
>
> To run GenSC with automatically selected parameters and a specific instance (for example: `rail-507.txt` in `Benchmarks/Rail/`):
>```shell
>./GenSC -inst ../Benchmarks/Rail/rail-507.txt
>```

- All of GenSC's parameters include

General Parameters:
> -_inst_ <path/to/instance> specifies the location of the instance (**required**)

> -_auto_ <0/1> whether to select algorithmic parameters automatically (default 1)

> -_print_sol_ <0/1> whether to print the solution after GenSC finished searching (see Output Format) (default 1)

> -_print_step_ <0/1> whether to print the steps during and after the search (see Output Format) (default 1)

> -_formatted_print_ <0/1> whether to print in a more human-friendly format (see Output Format) (default 1)


Specific Algorithmic Parameters:

> -_cutoff_time_ <integer in [1, 2147483647]> specifies the time GenSC is permitted to run (in seconds) (default 1000)

> -_seed_ <integer in [0, 2147483647]> specifies the seed (default 0)

> -_max_step_ <integer in [1, 9223372036854775807]> specifies the maximum step (iterations) of GenSC (default 9223372036854775807)

> -_perform_bms_ <0/1> whether to perform BMS heuristic (default 1)

> -_bms_t_ <integer in [1, 2147483647]> **Available Only When -_perform_bms_=1** (default 80)

> -_subset_score_calculation_ <1/2> (default 2)

> -_united_calculation_mu_ <integer in [2, 2147483647]> (default 5)

> -_solution_initialization_scheme_ <1-4> (default 4)

> -_perform_cc_ <0/1> (default 1)

> -_perform_iscc_ <0/1> (default 0)

> -_perform_tabu_ <0/1> (default 1)

> -_tabu_alpha_ <integer in [1, 2147483647]> (default 4)

> -_reconstruction_scheme_ <1-3> (default 1)

> -_reconstruct_swap_T_ <integer in [2, 2147483647]> **Available Only When -_reconstruction_scheme_=3** (default 5)

> -_subset_removal_scheme_ <1/2> (default 1)

> -_SAinitN_ <integer in <2, 5>> **Available Only When -_subset_removal_scheme_=2** (default 5) 

> -_SAt_ <integer in [1, 2147483647]> **Available Only When -_subset_removal_scheme_=2** (default 10000)

> -_subset_addition_scheme_ <1-5> (default 4)

> -_novel_addition_prob_ <float in [0, 1]> **Available Only When -_subset_addition_scheme_=2/4** (default 0.1)

> -_perform_alternate_method_ <1-4> (default 4)

> -_update_item_weights_scheme_ <1-3> (default 3)

> -_update_item_weights_SAPST_ <integer in [1, 2147483647]> **Available Only When -_update_item_weights_scheme_=1** (default 100) 

> -_update_item_weights_SAPSR_ <float in [0, 1]> **Available Only When -_update_item_weights_scheme_=1** (default 0.9)

> -_update_item_weights_PAWSP_ <float in [0, 1]> **Available Only When -_update_item_weights_scheme_=2** (default 0.8)

> -_subset_selection_scheme_ <1-9> (default 9)

However, some values of the parameters are prohibited since they are contradicted:

> **-_subset_score_calculation_=1 && _subset_selection_scheme_>3**

> **-_perform_alternate_method_=4 && -_subset_removal_scheme_=2**

- To run GenSC with optimal configurations for every benchmark:
>
> run
> ```
> ./GenSC -inst ../Benchmarks/...
> ```
> 
> or
> 
> **For Rail** 
>```shell
>./GenSC -perform_bms 1 -bms_t 5000 -subset_score_calculation 2 -united_calculation_mu 3 -solution_initialization_scheme 1 -perform_cc 1 -perform_iscc 0 -perform_tabu 1 -tabu_alpha 80 -reconstruction_scheme 2 -subset_removal_scheme 1 -subset_addition_scheme 4 -novel_addition_prob 0.21 -perform_alternate_method 4 -update_item_values_scheme 3 -subset_selection_scheme 8 -inst ../Benchmarks/Rail/...
>```
>
> **For SCP-CLR** 
>```shell
>./GenSC -perform_bms 1 -bms_t 170 -subset_score_calculation 2 -united_calculation_mu 80 -solution_initialization_scheme 4 -perform_cc 1 -perform_iscc 0 -perform_tabu 1 -tabu_alpha 5 -reconstruction_scheme 2 -subset_removal_scheme 1 -subset_addition_scheme 4 -novel_addition_prob 0.5 -perform_alternate_method 4 -update_item_values_scheme 3 -subset_selection_scheme 9 -inst ../Benchmarks/SCP-CLR/...
>```
>
> **For SCP-CYC** 
>```shell
>./GenSC -perform_bms 1 -bms_t 230 -subset_score_calculation 2 -united_calculation_mu 200 -solution_initialization_scheme 3 -perform_cc 0 -perform_iscc 1 -perform_tabu 0 -reconstruction_scheme 1 -subset_removal_scheme 2 -SAinitN 4 -SAt 50000 -subset_addition_scheme 2 -novel_addition_prob 0.1 -perform_alternate_method 2 -update_item_values_scheme 3 -subset_selection_scheme 2 -inst ../Benchmarks/SCP-CYC/...
>```
> 
> **For STS** 
>```shell
>./GenSC -perform_bms 1 -bms_t 150 -subset_score_calculation 2 -united_calculation_mu 70 -solution_initialization_scheme 3 -perform_cc 1 -perform_iscc 0 -perform_tabu 1 -tabu_alpha 3 -reconstruction_scheme 1 -subset_removal_scheme 1 -subset_addition_scheme 3 -perform_alternate_method 4 -update_item_values_scheme 3 -subset_selection_scheme 8 -inst ../Benchmarks/STS/...
>```
>
> **For SoftTest-S** 
>```shell
>./GenSC -perform_bms 0 -subset_score_calculation 2 -united_calculation_mu 11 -solution_initialization_scheme 1 -perform_cc 0 -perform_iscc 0 -perform_tabu 1 -tabu_alpha 30 -reconstruction_scheme 1 -subset_removal_scheme 1 -subset_addition_scheme 3 -perform_alternate_method 1 -update_item_values_scheme 3 -subset_selection_scheme 7 -inst ../Benchmarks/SoftTest-S/...
>```
> 
> **For SoftTest-M** 
>```shell
>./GenSC -perform_bms 1 -bms_t 800 -subset_score_calculation 2 -united_calculation_mu 4 -solution_initialization_scheme 4 -perform_cc 0 -perform_iscc 0 -perform_tabu 1 -tabu_alpha 100 -reconstruction_scheme 2 -subset_removal_scheme 2 -SAinitN 4 -SAt 30000 -subset_addition_scheme 3 -perform_alternate_method 2 -update_item_values_scheme 3 -subset_selection_scheme 9 -inst ../Benchmarks/SoftTest-M/...
>```
> 
> **For SoftTest-L** 
>```shell
>./GenSC -perform_bms 1 -bms_t 300 -subset_score_calculation 2 -united_calculation_mu 15 -solution_initialization_scheme 1 -perform_cc 0 -perform_iscc 0 -perform_tabu 1 -tabu_alpha 10 -reconstruction_scheme 2 -subset_removal_scheme 1 -subset_addition_scheme 3 -perform_alternate_method 2 -update_item_values_scheme 3 -subset_selection_scheme 9 -inst ../Benchmarks/SoftTest-L/...
>```

- To run GenSC with custom configurations:
> run
> ```
> ./GenSC -auto 0 ...
> ```
> Note that **-auto 0** is required

## Output Format

- The output file of GenSC consist of lines starting with **'c'**, **'o'** and **'v'**, **'c'** for comments, **'o'** for output and **'v'** for detailed solution. A typical output (with default parameters) may look like:

```shell
c
c GenSC -- A Novel and General Local Search Framework for Set Covering Problem (SCP)
c Version: 1.0
c
c best_weight best_time best_step
o         181      0.14        10
o         180      0.21        15
c total step: 20
c set_cover_weight: 180 run_time: 0.21 best_step: 15
c detailed_set_cover: 
v 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 ......
```

- As labeled in the output, the three numbers in a line starting with **'o'** are: the best weight found, the time of finding the best weight in seconds, the step of finding the best weight. 
- At last GenSC outputs a summary of steps, weight and runtime then a line starting with **'v'** containing specific results.

> The output format can be customized using parameters -_print_sol_, -_print_step_ and -_formatted_print_.
> 
> `-print_sol` determines whether to print the detailed solution (the line starting with **'v'**). Select 0 to disable.
> 
> `-print_step` determines whether to print the information related to steps (best_step and total step). Select 0 to disable.
>
> `-formatted_print` determines whether to print as above (selecting 1), or GenSC will print simply as follows (selecting 0).
> ```shell
> c
> c GenSC -- A Novel and General Local Search Framework for Set Covering Problem (SCP)
> c Version: 1.0
> c
> o 181
> o 180
> c total step: 20
> c set_cover_weight: 180 run_time: 0.21 best_step: 15
> c detailed_set_cover: 
> v 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 ......
