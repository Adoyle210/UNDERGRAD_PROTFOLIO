// set up:
var cors = require('cors')
var express = require('express')
var app = express()
PORT = 111111
var fs = require('fs')
var db = require('./db-connector')

app.use(express.json())
app.use(express.static('public'))
app.use(cors())

//routes:
app.get('/', function(req, res) {
    res.status(201).sendFile(__dirname + 'public/pokedex.html')
})

app.get('/api/pokedex/get', function(req, res) {
    console.log('get request made')
    query = 'SELECT * FROM pokedex;'
    db.pool.query(query, function(err, result, fields) {
        if (err) {
            console.log(err)
            res.status(404)
        }
        console.log(result)
        res.status(201).send(JSON.stringify(result))
    })
})

app.post('/api/pokedex/add', function(req, res) {
    console.log('post request made')
    query = "INSERT INTO pokedex (pname, ptype, regionID) VALUES ('" + req.body.pname + "', '" + req.body.ptype + "', '" + req.body.regionID + "');"
    db.pool.query(query, function(err, result, fields) {
        if (err) {
            console.log(err)
            res.status(404)
        }
        console.log(result)
        res.status(201).send(JSON.stringify(result))
    })
})

app.delete(`/api/pokedex/delete/:pname`, function(req, res) {
    console.log('delete request made')
    query = "DELETE FROM pokedex WHERE pokedexID = " + req.params.pokedexID + ';'
    db.pool.query(query, function(err, result, fields) {
        if (err) {
            console.log(err)
            res.status(404)
        }
        console.log(result)
        res.status(202).send("pokedex entry deleted")
    })
})

app.put(`/api/pokedex/update/:accID`, function(req, res) {
    console.log('put request made')
    query = "UPDATE pokedex SET pname = '" + req.body.pname + "', ptype = '" + req.body.ptype + "', regionID = '" + req.body.regionID + "' where pokedexID = " + req.params.pokedexID + ";"
    //console.log(req)
    db.pool.query(query, function(err, result, fields) {
        if (err) {
            console.log(err)
            res.status(404)
        }
        console.log(result)
        res.status(202).send("account updated")
    })
})


/*
* LISTENER
*/

app.listen(PORT, function() {
    console.log('Listening on PORT ' + PORT)
})