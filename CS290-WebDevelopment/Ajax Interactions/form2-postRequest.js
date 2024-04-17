document.addEventListener("DOMContentLoaded", bind);

function bind(){
    document.getElementById("submitInfo").addEventListener("click", function(event){
      var req = new XMLHttpRequest();
      var site = "http://httpbin.org/post";
      var payload = {                         //The payload to be delivered with initial null values
          "song": null,                                   //These will be set next
          "artist": null
      };
      payload.song = document.getElementById("song").value; //set value for payload
      payload.artist = document.getElementById("artist").value;

      req.open("POST", site, true);   //set true to send Asynchronously
      req.setRequestHeader("Content-Type", "application/json");
      req.addEventListener("load",function(){
        if(req.status >= 200 && req.status < 400){ //only displays if no errors have occured
            var response = JSON.parse(JSON.parse(req.responseText).data);
            displayResults(response);
        }
        else{
            console.log("error");
        }
      });
      req.send(JSON.stringify(payload));  //sending the request
      event.preventDefault();
    });
}

function displayResults(response){          //function sets returns
    document.getElementById("songReturn").textContent = response.song;
    document.getElementById("artistReturn").textContent = response.artist;

}
