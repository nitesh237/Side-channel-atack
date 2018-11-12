var i = 0;
var lineArr;
function reader() 
{
	document.getElementById("sb_form_q").value = lineArr[i];
	console.log(lineArr[i]);
	i++;	
}


function readTextFile(file)
{
    var rawFile = new XMLHttpRequest();
    rawFile.open("GET", file, false);
    rawFile.onreadystatechange = function ()
    {
        if(rawFile.readyState === 4)
        {
            if(rawFile.status === 200 || rawFile.status == 0)
            {
                var allText = rawFile.responseText;
				lineArr = allText.split('\n');
				setInterval(reader, 3500);
                alert(allText);
            }
        }
    }
    rawFile.send(null);
}

readTextFile("https://raw.githubusercontent.com/nitesh237/words/master/final3.txt");