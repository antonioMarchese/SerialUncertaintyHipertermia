<h1>SerialUncertaintyHipertermia</h1>

This is an extension of the code created in the 'SerialHipertermia' repository, in which experiments have been added so that the uncertainty of the parameters in several simulations can be studied. This way, at the end of the execution the program saves the mean and the standard deviation of the temperature for the stipulated time steps. With the files saved in the '.txt' format, it is possible to use them in the code present in 'temp.py' to generate heat graphs (in 2D) and graphs analyzing the mean and standard deviation of the temperature in specific points of the tissue. <br />
To compile (linux): <br />
<h3> $ g++ &nbsp; -lm &nbsp; -O3 &nbsp; main.cpp &nbsp; -o &nbsp; 'file name' &nbsp; <h3 /> <br />
To execute: $ ./'file name'

-----------------------------------------------------------------------------------------------------------------------------------------------------------

Essa é uma extensão do código criado no repositório 'SerialHipertermia', no qual foram adicionados experimentos para que se possa estudar a incerteza dos parâmetros em várias simulações. Dessa forma, ao final da execução, o programa salva a média e o desvio padrão da temperatura para os passos de tempo estipulados. Com os arquivos salvos no formato '.txt', é possível utilizá-los no código presente em 'temp.py' para gerar gráficos de calor (em 2D) e gráficos analisando a média e o desvio padrão da temperatura em pontos específicos do tecido. <br />
Para compilar esse programa, deve-se usar (em linux): $ g++ &nbsp; -lm &nbsp; -O3 &nbsp; main.cpp &nbsp; -o &nbsp; 'file name' &nbsp; <br />
Para executá-lo: $ ./'Nome do executável'
   
