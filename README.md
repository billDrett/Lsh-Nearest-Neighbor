<h1/>Lsh-Nearest-Neighbor</h1>
LSH is an algorithm for solving the aproximate or exact Near Neighbor Search in high dimensional spaces. LSH hashes input items so that similar items map to the same “buckets” with high probability </br>
<b>It finds:</b></br>
<lu>
<li>The nearest neighbor of a given point q </li>
<li>The neighbors of q in a range with radius R</li>
</lu>
List and hashtable structure are created because STL wasn't allowed in the class

<h2>Support</h2>
The LSH algorithm supports:</br>
<lu>
<li>Euclidean  Vector Space</li>
<li>Cosine Vector Space</li>
<li>Hamming Metric Space</li>
<li>Distance Matrix Metric Space</li></lu>
See the <a href="https://github.com/billDrett/Lsh-Nearest-Neighbor/blob/master/dataTypes.h">datatypes file</a> for the format of each metric space.

<h2>Compile</h2>
Use make command to compile and make clean to delete object files(there is a MakeFile). 

<h2>Run</h2>
./lsh –d &lt;input file&gt; –q &lt;query file&gt; –k &lt;int&gt; -L &lt;int&gt; -ο &lt;outputfile&gt; </br>
-d &lt;input file>: The input file name</br>
-ο &lt;output file>: Output file name </br>
–q &lt;query file>: query file name, format is</br>
-k &lt;int>: The number of hi for the hashfunctions (the number of buckets in hashtables 2^k), default value 4</br>
-L &lt;int>: The number of hashTables in Lsh, default value 5.</br>

<h2>Functionality</h2>
The input data are hashed in L hashtables. Each hashtable has its own hashfunction, the hashfunction is created randomly based on the k number of hi and its different depending on the metric space. More about the hashfunctions can be found on the papers. </br>
After the query points are used to find the nearest neighbors and the neighbors which are within a radius. </br>
The output consists of the query point, the R-nead neighbors, the nearest neighbor, the distance of the nearest, the time for the calculation and the true nearest with the brute force method.

<h2>Files</h2>
Format of input file:</br>
<b>Vector space</b></br>
@metric_space vector </br>
@metric {euclidean, cosine} //default: euclidean</br>
item_id1  x11 x12 ... x1d</br>
item_id2</br>
.</br>
.</br>
item_idN  xN1 xN2 ... xNd</br></br>
<b>Hamming</b></br>
@metric_space hamming</br>
item_id1  B1</br>
....</br>
item_idN</br></br>
<b>Distance Matrix</b></br>
@metric_space matrix </br>
item_id1  x11 x12 ... x1d</br>
item_id2</br>
.</br>
.</br>
item_idQ  xQ1 xQ2 ... xQd</br></br>

<b>Query File</b></br>
Radius: &lt;double> </br>
item_id1  x11 x12 ... x1d</br>
item_id2</br>
.</br>
.</br>
item_idQ  xQ1 xQ2 ... xQd</br>



