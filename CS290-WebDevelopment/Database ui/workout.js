var express = require("express");              
var app = express();
var bodyParser = require("body-parser"); 
var handlebars = require("express-handlebars").create({defaultLayout: "main"});
var mysql = require("mysql");

var pool = mysql.createPool({                   //made a pool in this doc instead of using a dbcon.js file
    host: "classmysql.engr.oregonstate.edu",        
    user: "cs290_doylalex",
    password: "1869",                           //this info should normally be hidden like said in class videos 
    database: "cs290_doylalex"
});

app.engine("handlebars", handlebars.engine);        
app.set("view engine", "handlebars");
app.set("port", 18697);                              //port i set up 
app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());
app.use(express.static("public"));
/*******************************************************************
* description: this function allows us to compeletly 
* reset the table when revisiting the url that is given
********************************************************************/
app.get('/reset-table',function(req,res,next){                 
    var context = {};
    pool.query("DROP TABLE IF EXISTS workouts", function(err){
        var createString = "CREATE TABLE workouts("+
        "id INT PRIMARY KEY AUTO_INCREMENT,"+
        "name VARCHAR(255) NOT NULL,"+
        "reps INT,"+
        "weight INT,"+
        "date DATE,"+
        "lbs BOOLEAN)";
        pool.query(createString, function(err){
            res.render('table',context);
        })
    });
});

/*******************************************************************
* description: this function is the basic set up for the table
* it accesses and keeps track of parameters and displays the 
* data in the table 
********************************************************************/
app.get('/', function(req, res, next){
    var context = {};
    pool.query('SELECT * FROM workouts', function(err, rows, fields){           //pool is directly coded into the file, we don't need mysql preface
    if(err){                                                                    //this selects all items from the table
        next(err);
        return;
    }
    var params = [];                                //each item we keep track of its parameters
    for(var row in rows){
        var addItem = {'name': rows[row].name, 
                    'reps': rows[row].reps, 
                    'weight': rows[row].weight, 
                    'date':rows[row].date, 
                    'id':rows[row].id};
        if(rows[row].lbs){
            addItem.lbs = "lbs";
        }
        else{
            addItem.lbs = "kg";
        }
        params.push(addItem);                   //we use push to add all the parameters we kept track of 
    }
    context.results = params;
    res.render('table', context);               //display the table
    })
});

/*******************************************************************
* description: this function is for inserting 
********************************************************************/
app.get('/insert',function(req,res,next){
  var context = {};
   pool.query("INSERT INTO `workouts` (`name`, `reps`, `weight`, `date`, `lbs`) VALUES (?, ?, ?, ?, ?)", //'?' to indicate user supplied data (just like in assembly language)
    [req.query.exercise,                //all of these are required to prevent database from being messed with
    req.query.reps, 
    req.query.weight, 
    req.query.date, 
    req.query.unitCheck], 
    function(err, result){
        if(err){
          next(err);
          return;
        }         
        context.inserted = result.insertId;
        res.send(JSON.stringify(context));
  });
});

/*******************************************************************
* description: this function is for deleting it requires 
* the items id so it can be found and deleted 
********************************************************************/
app.get('/delete', function(req, res, next) {
    var context = {};    
    pool.query("DELETE FROM `workouts` WHERE id = ?",   //when we call delete on the database and require the id  
        [req.query.id], 
        function(err, result) {
            if(err){
                next(err);
                return;
            }
    });
});

/*******************************************************************
* description: this function is for table updates 
* this requries the id like delete so the user 
+ updates the proper one 
********************************************************************/
app.get('/updateTable',function(req, res, next){
    var context = {};
    pool.query('SELECT * FROM `workouts` WHERE id=?',   //selects all with the id we want
        [req.query.id], 
        function(err, rows, fields){
            if(err){
                next(err);
                return;
            }
            var param = [];

            for(var row in rows){                           //this part is similar to the adding 
                var addItem = {'name': rows[row].name, 
                            'reps': rows[row].reps, 
                            'weight': rows[row].weight, 
                            'date':rows[row].date, 
                            'lbs':rows[row].lbs,
                            'id':rows[row].id};

                param.push(addItem);
            }

        context.results = param[0];                      //this makes sure the object goes to updateTable page
        res.render('updateTable', context);
    });
});

/*******************************************************************
* description: this function returns updates and it also still needs
* the id to make sure we are dealing with the proper parameters/data
********************************************************************/
app.get('/updateReturn', function(req, res, next){
    var context = {};

    pool.query("SELECT * FROM `workouts` WHERE id=?", //again we requrie the id and use '?'
        [req.query.id], 
        function(err, result){
            if(err){
                next(err);
                return;
            }
            if(result.length == 1){                
                var current = result[0];

                
                if(req.query.unitCheck === "on"){
                    req.query.unitCheck = "1";
                }
                else{
                    req.query.unitCheck = "0";
                }

                pool.query('UPDATE `workouts` SET name=?, reps=?, weight=?, date=?, lbs=? WHERE id=?',  //we make a query to UPDATE and require either what the name is now or the updated name
                [req.query.exercise || current.name, 
                req.query.reps || current.reps, 
                req.query.weight || current.weight, 
                req.query.date || current.date, 
                req.query.unitCheck, 
                req.query.id],
                function(err, result){
                    if(err){
                        next(err);
                        return;
                    }

                    pool.query('SELECT * FROM `workouts`', function(err, rows, fields){     
                        if(err){
                            next(err);
                            return;
                        }
                        var param = [];

                        for(var row in rows){
                            var addItem = {'name': rows[row].name,      //once again this is similar to adding
                            'reps': rows[row].reps,
                            'weight': rows[row].weight, 
                            'date':rows[row].date, 
                            'id':rows[row].id};

                            if(rows[row].lbs){              //this is determines lbs and kg
                                addItem.lbs = "lbs";
                            }
                            else{
                                addItem.lbs = "kg";
                            }
                            param.push(addItem);            //this pushes the items so they can be displayed
                        }

                        context.results = param;
                        res.render('table', context);       //everything now gets displayed
                    });
                });
            }
    });
});

/*******************************************************************
* the following is standard error handleing 
********************************************************************/
app.use(function(req, res){                 
	res.status(404);
	res.render("404");
});

app.use(function(err, req, res, next){
	console.log(err.stack);
	res.status(500);
	res.render("500");
});

app.listen(app.get("port"), function(){             //checks the port 
	console.log("Express started on port 18697");
});

