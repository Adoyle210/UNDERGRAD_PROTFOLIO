// Your code here.
var deepEqual = function (x, y) {
  if (x === y) {  //checks if x and y should be compared directly 
    return true;
  }
  else if ((typeof x == "object" && x != null) && (typeof y == "object" && y != null)) { //if == to object and checks for NULL
    if (Object.keys(x).length != Object.keys(y).length){ //key checks properites (names and values)
      return false;
    }
    for (var prop in x) {		//for ... in
      if(! deepEqual(x[prop],y[prop])){ //recursive calling of deepEqual to check properties
      	return false;
      }
    }
    return true; // passes the for ... in test so returns true
  }
  else{			// returns false if x !== y
    return false;
   }
}

let obj = {here: {is: "an"}, object: 2};
console.log(deepEqual(obj, obj));
// → true
console.log(deepEqual(obj, {here: 1, object: 2}));
// → false
console.log(deepEqual(obj, {here: {is: "an"}, object: 2}));
// → true
