// set up:
var cors = require('cors')
var express = require('express')
var app = express()
PORT = 65532
var fs = require('fs')
var db = require('./database/db')

app.use(express.json())
app.use(express.static('public'))
app.use(cors())

//GETS
app.get('/', function(req, res) {
    res.status(201).sendFile(__dirname + '/public/pokedex.html')
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

app.get('/api/trainer/get', function(req, res) {
    console.log('get request made')
    query = 'SELECT * FROM trainer;'
    db.pool.query(query, function(err, result, fields) {
        if (err) {
            console.log(err)
            res.status(404)
        }
        console.log(result)
        res.status(201).send(JSON.stringify(result))
    })
})

app.get('/api/trainerHas/get', function(req, res) {
    console.log('get request made')
    query = 'SELECT * FROM trainerHas;'
    db.pool.query(query, function(err, result, fields) {
        if (err) {
            console.log(err)
            res.status(404)
        }
        console.log(result)
        res.status(201).send(JSON.stringify(result))
    })
})


//POSTING N GHOSTING :))))

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

app.post('/api/trainer/add', function(req, res) {
    console.log('post request made')
    query = "INSERT INTO trainer (tname, wins, losses) VALUES ('" + req.body.tname + "', '" + req.body.wins + "', '" + req.body.losses + "');"
    db.pool.query(query, function(err, result, fields) {
        if (err) {
            console.log(err)
            res.status(404)
        }
        console.log(result)
        res.status(201).send(JSON.stringify(result))
    })
})

// app.post('/api/trainerHas/add', function(req, res) {
//     console.log('post request made')
//     query = "INSERT INTO trainer (pokedexID, PokemonID) VALUES ('" + req.body.pokedexID + "', '" + req.body.pokemonID+ "');"
//     db.pool.query(query, function(err, result, fields) {
//         if (err) {
//             console.log(err)
//             res.status(404)
//         }
//         console.log(result)
//         res.status(201).send(JSON.stringify(result))
//     })
// })

//DELETING ... 
app.delete(`/api/pokedex/delete/:pokedexID`, function(req, res) {
    console.log('delete request made')
    query = "DELETE FROM pokedex WHERE pokedexID = " + req.params.pokedexID + ";"
    db.pool.query(query, function(err, result, fields) {
        if (err) {
             console.log(err)
             res.status(404)
         }
         console.log(result)
         res.status(202).send("pokedex entry deleted", query)
    })
})

app.delete(`/api/trainer/delete/:trainerID`, function(req, res) {
    console.log('delete request made')
    query = "DELETE FROM trainer WHERE trainerID = " + req.params.trainerID + ";"
    db.pool.query(query, function(err, result, fields) {
        if (err) {
             console.log(err)
             res.status(404)
         }
         console.log(result)
         res.status(202).send("trainer entry deleted", query)
    })
})


//UPDATING yeahhh
app.put(`/api/pokedex/update/:pokedexID`, function(req, res) {
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

app.put(`/api/pokedex/update/:trainerID`, function(req, res) {
    console.log('put request made')
    query = "UPDATE trainer SET tname = '" + req.body.tname + "', wins = '" + req.body.wins + "', losses = '" + req.body.losses + "' where trainerID = " + req.params.trainerID + ";"
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
