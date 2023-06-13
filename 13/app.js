/*
    SETUP
*/
var express = require('express');   // We are using the express library for the web server
var app     = express();            // We need to instantiate an express object to interact with the server in our code
PORT        = 64222;                 // Set a port number at the top so it's easy to change in the future

// database
var db = require('./database/db-connector');

// express 
app.use(express.json())
app.use(express.urlencoded({extended: true}))
app.use(express.static('public'))

// handlebars
const { engine } = require('express-handlebars');
var exphbs = require('express-handlebars');     // Import express-handlebars
app.engine('.hbs', engine({extname: ".hbs"}));  // Create an instance of the handlebars engine to process templates
app.set('view engine', '.hbs');                 // Tell express to use the handlebars engine whenever it encounters a *.hbs file.

/*
    ROUTES
*/
//GETS 
app.get('/', function(req, res)                 // This is the basic syntax for what is called a 'route'
{
    let query1 = "SELECT * FROM pokedex;";
    let query2 = "SELECT * FROM type;";
    let query3 = "SELECT * FROM region;";
    db.pool.query(query1, function(error, rows, fields){
        //saving pokedex data
        let poke = rows;

        db.pool.query(query2, (error, rows, fields) => {
            //saving types
            let types = rows;

            db.pool.query(query3, (error, rows, fields) => {
                //saving region 
                let regions = rows;

                return res.render('pokedex', {data: poke, types: types, regions: regions}); 
            })
        })
        
    })     
});                                         // requesting the web site.

app.get('/trainer', function(req, res)                 // This is the basic syntax for what is called a 'route'
{
    let query1 = "SELECT * FROM trainer;";
    db.pool.query(query1, function(error, rows, fields){
        res.render('trainer', {data: rows}); 
    })     
}); 

app.get('/trainerHas', function(req, res)                 // This is the basic syntax for what is called a 'route'
{
    let query1 = "SELECT * FROM trainerHas;";
    let query2 = "SELECT * FROM pokedex;";
    let query3 = "SELECT * FROM trainer;";
    db.pool.query(query1, function(error, rows, fields){
        let trainer = rows;
        db.pool.query(query2, (error, rows, fields) => {
            //savving pokedex
            let poke = rows;
            db.pool.query(query3, (error, rows, fields) => {
                //saving type
                let trainers = rows;

                return res.render('trainerhas', {data: trainer, pokedex: poke, trainer: trainers}); 
            })
        })    
    })        
}); 

app.get('/type', function(req, res)                 // This is the basic syntax for what is called a 'route'
{
    let query1 = "SELECT * FROM type;";
    db.pool.query(query1, function(error, rows, fields){
        res.render('type', {data: rows}); 
    })     
}); 

app.get('/type/search', function (req, res) {
    let query1;

    if (req.query.searchedType === undefined || req.query.searchedType == '') {
      query1 = 'SELECT * FROM type;';
    } else {
      let searchedTitle = req.query.searchedTitle;
      query1 = `SELECT * FROM type WHERE title LIKE '%${searchedType}%'`;
    }
  
    db.pool.query(query1, function (error, rows, fields) {
      if (error) {
        console.log(error);
        res.sendStatus(400);
      } else {
        res.render('type', { data: rows });
      }
    });
  });

app.get('/region', function(req, res)                 // This is the basic syntax for what is called a 'route'
{
    let query1 = "SELECT * FROM region;";
    db.pool.query(query1, function(error, rows, fields){
        res.render('region', {data: rows}); 
    })     
}); 


//POST
app.post('/pokedex/add', function(req, res) {
    query1 = "INSERT INTO pokedex (pname, ptype, regionID) VALUES ('" + req.body.pname + "', '" + req.body.ptype + "', '" + req.body.regionID + "');"
    db.pool.query(query1, function(err, result, fields){
        if (err) {
            console.log(err);
            res.sendStatus(400);
        }
        else {
            query2 = "SELECT * FROM pokedex;";
            db.pool.query(query2, function(err, result, fields){
                if (err) {
                    console.log(err);
                    res.sendStatus(400);
                }
                else {
                    res.send(result);
                }
            })   
        }
    })
});

app.post('/trainer/add', function(req, res) {
    query1 = "INSERT INTO trainer (tname, wins, losses) VALUES ('" + req.body.tname + "', '" + req.body.wins + "', '" + req.body.losses + "');"
    db.pool.query(query1, function(err, result, fields){
        if (err) {
            console.log(err);
            res.sendStatus(400);
        }
        else {
            query2 = "SELECT * FROM trainer;";
            db.pool.query(query2, function(err, result, fields){
                if (err) {
                    console.log(err);
                    res.sendStatus(400);
                }
                else {
                    res.send(result);
                }
            })   
        }
    })
});

app.post('/trainerHas/add', function(req, res) {
    query1 = "INSERT INTO trainerHas (trainerID, pokedexID) VALUES ('" + req.body.trainerID + "', '" + req.body.pokedexID + "');"
    db.pool.query(query1, function(err, result, fields){
        if (err) {
            console.log(err);
            res.sendStatus(400);
        }
        else {
            query2 = "SELECT * FROM trainerHas;";
            db.pool.query(query2, function(err, result, fields){
                if (err) {
                    console.log(err);
                    res.sendStatus(400);
                }
                else {
                    res.send(result);
                }
            })   
        }
    })
});

app.post('/type/add', function(req, res) {
    //catching null 
    let type2 = parseInt(req.body.type2);
    if (isNaN(type2))
    {
        type2 = 'NULL'
    }

    query1 = "INSERT INTO type (type1, type2) VALUES ('" + req.body.type1 + "', '" + req.body.type2 + "');"
    db.pool.query(query1, function(err, result, fields){
        if (err) {
            console.log(err);
            res.sendStatus(400);
        }
        else {
            res.send(result);  
        }
    })
}); 

app.post('/region/add', function(req, res) {
    query1 = "INSERT INTO region (region1, region2) VALUES ('" + req.body.region1 + "', '" + req.body.region2 + "');"
    db.pool.query(query1, function(err, result, fields){
        if (err) {
            console.log(err);
            res.sendStatus(400);
        }
        else {
            query2 = "SELECT * FROM region;";
            db.pool.query(query2, function(err, result, fields){
                if (err) {
                    console.log(err);
                    res.sendStatus(400);
                }
                else {
                    res.send(result);
                }
            })   
        }
    })
});

//DELETE
app.delete('/pokedex/delete/', function(req,res,next){
    let data = req.body;
    let pokedexID = parseInt(data.id);
    let query1 = `DELETE FROM pokedex WHERE PokedexID = ?`;
    // Run the 1st query
    db.pool.query(query1, [pokedexID], function(error, rows, fields){
        if (error) {
            console.log(error);
            res.sendStatus(400);
        }
        else {
            res.sendStatus(204);
        }
    })
});

//UPDATE
app.put('/pokedex/update', function(req,res,next){
    let data = req.body;
  
    let pname = parseInt(data.pname);
    let ptype = parseInt(data.ptype);
    let regionID = parseInt(data.regionID);
    let pokedexID = parseInt(data.pokedexID);
  
    let query1 = `UPDATE pokedex SET pname = ?, ptype = ?, regionID = ? WHERE pokedexID = ?`;
    db.pool.query(query1, [pname, ptype, regionID, pokedexID], function(error, rows, fields){
        if (error) {
            console.log(error);
            res.sendStatus(400);
        }
        else {
            res.send(rows);
        }
    })
});

/*
    LISTENER 
*/
app.listen(PORT, function(){            // This is the basic syntax for what is called the 'listener' which receives incoming requests on the specified PORT.
    console.log('Express started on http://flip3.engr.oregonstate.edu/:' + PORT + '; press Ctrl-C to terminate.')
});