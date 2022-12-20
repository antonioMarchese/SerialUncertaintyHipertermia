<h1>Serial Uncertainty Hipertermia</h1>

<h3>Calculates the mean and the standard deviation of tissue temperature</h3>

<p> This is an extension of the code created in the 'SerialHipertermia' repository (<a href="https://github.com/antonioMarchese/SerialHipertermia">https://github.com/antonioMarchese/SerialHipertermia </a>), in which experiments have been added so that the uncertainty of the parameters in several simulations can be studied. This way, at the end of the execution the program saves the mean and the standard deviation (sdv) of the temperature for the stipulated time steps. </p> 
<h3>To compile</h3>
<h4> $ g++ -lm -O3 main.cpp -o 'file name'</h4> 
<h3>To execute</h3>
<h4> $ ./'file name'</h4>
<p>Then, in your 'temp.py', with the files saved in the '.txt' format, it is possible to use them to: </p>
<ul>
   <li>Generate heatmaps</li>
   <li>Create graphs analyzing the mean and standard deviation of the temperature in specific points of the tissue.</li>
</ul>
<h3>To create heatmaps</h3>
<h4>create_heatmap()</h4>
<h3>To plot temperature mean and sdv of both healthy and diseased tissue</h3>
<h4>plot_temp()</h4>

-----------------------------------------------------------------------------------------------------------------------------------------------------------

<h1>Learn more</h1>
<p>You can learn more about it in this<a href="https://www.sciencedirect.com/science/article/pii/S0377042715001247"> paper</a></p>
   
