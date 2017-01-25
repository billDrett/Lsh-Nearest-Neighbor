<h1/>Lsh-Nearest-Neighbor</h1>
LSH is an algorithm for solving the aproximate or exact Near Neighbor Search in high dimensional spaces. </br>
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

<h2>Compile</h2>
Use make command to compile and make clean to delete object files(there is a MakeFile). 

<h2>Run</h2>
./lsh –d &lt;input file&gt; –q &lt;query file&gt; –k &lt;int&gt; -L &lt;int&gt; -ο &lt;outputfile&gt; </br>
-d &lt;input file>: The input file name</br>
-ο &lt;output file>: Output file name </br>
–q <query file>: query file name, format is</br>
-k &lt;int>: The number of hi for the hashfunctions (the number of buckets in hashtables 2^k), default value 4</br>
-L &lt;int>: The number of hashTables in Lsh, default value 5.</br>
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



