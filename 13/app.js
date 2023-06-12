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
    db.pool.query(query1, function(error, rows, fields){
        res.render('pokedex', {data: rows}); 
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
    db.pool.query(query1, function(error, rows, fields){
        res.render('trainerhas', {data: rows}); 
    })     
}); 

app.get('/type', function(req, res)                 // This is the basic syntax for what is called a 'route'
{
    let query1 = "SELECT * FROM type;";
    db.pool.query(query1, function(error, rows, fields){
        res.render('type', {data: rows}); 
    })     
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

// app.post('/pokedex/add', funcion(req, res){
//     query1 = "INSERT INTO pokedex (pname, ptype, regionID) VALUES ('" + req.body.pname + "', '" + req.body.ptype + "', '" + req.body.regionID + "');"
//     db.pool.query(query1, function(err, result, fields){
//         if (err) {
//             console.log(err);
//             res.status(404);
//         }
//         else {
//             query2 = "SELECT * FROM pokedex;";
//             db.pool.query(query2, function(error, result, fields){
//                 if (err) {
//                     console.log(err);
//                     res.status(404);
//                 }
//                 else {
//                     res.send(result);
//                 }
//             })   
//         }
//     })
// });

/*
    LISTENER 
*/
app.listen(PORT, function(){            // This is the basic syntax for what is called the 'listener' which receives incoming requests on the specified PORT.
    console.log('Express started on http://flip3.engr.oregonstate.edu/:' + PORT + '; press Ctrl-C to terminate.')
});