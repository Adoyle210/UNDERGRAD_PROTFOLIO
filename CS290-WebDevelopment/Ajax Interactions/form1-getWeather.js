document.addEventListener('DOMContentLoaded', getData);

function getData() {
		document.getElementById('getWeather').addEventListener('click', function(event){
				var req = new XMLHttpRequest();
				var appID = "&appid=46db78e85004163df9ea0b9c0ff27c3c"; //free app id from account
				var code = document.getElementById("code").value; //geting countryCode
				var zip = document.getElementById("zip").value; // getting zipCode
    		var city = document.getElementById("city").value; //getting cityName
    		var payload;

    		if(zip == 5){
        	payload = "http://api.openweathermap.org/data/2.5/weather?zip=" + zip + "," +code + appID + '&units=imperial';      //Add imperial to query to get imperial units (from documentation)
    		}
    		else{
        	payload = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + code + appID + '&units=imperial';
    		}
				req.open("GET", payload, true);                             //Set true to send asynchronous request
				req.addEventListener('load', function() {                   //Want the function to execute once everything loads
			   		if (req.status >= 200 && req.status < 400) {             //checking for error
				       	var response = JSON.parse(req.responseText);
				       	displayWeather(response);                       //Call the function to display the information
			   		}
         		else {
				      	console.log("error");
			   		}
     		});
		    req.send();
		    event.preventDefault();
  	});
}

function displayWeather(response){
    document.getElementById("mainTemp").textContent = response.main.temp;               //display the weather data
    document.getElementById("weatherHumidity").textContent = response.main.humidity;
    document.getElementById("weatherSpeed").textContent = response.wind.speed;
    document.getElementById("sunriseStart").textContent = response.sys.sunrise;
}
