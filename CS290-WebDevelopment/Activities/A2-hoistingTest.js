console.log(addOne(1)); //calls before
function addOne(x){
    console.log("With hoisting!!")
  console.log(x +" + 1 =")
  return x + 1;
}
console.log(addOne(2)); //calls after
//console.log(addTwo(1));    //calls before and causes an error
var addTwo = function(x){
    console.log("without hoisting!!")
  console.log(x +" + 2 =")
  return x + 2;
}
console.log(addTwo(2));    //calls after 
