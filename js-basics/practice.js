let a = 0.1;
let b = 0.2;
let c =0.3;

if( (a+b).toPrecision(1) == c.toPrecision(1) ){
    console.log('yay');
}

a


	
// promise 
var promise = new Promise(function(resolve, reject) {
    resolve('returns this value when resolved.');
});
promise.then(function(value) {
    console.log(value);
});

var anotherPromise = new Promise(function(resolve, reject) {
    resolve("another resolved value... ");
});
// handling multiple promises 
Promise.all([promise,anotherPromise]).then(function (resultArr){
	console.log(resultArr)// result is in order 
})
Promise.race([promise,anotherPromise]).then(function (firstResult){
	console.log(firstResult)// result is in order 
})

console.log("-------------------------------------------------------------------------")

//clousure: 
function add(a) { // a =2
   	return function (b) { // b = 3
    	return a+b
   }
}

console.log(add(2)(3)) // 5

console.log("-------------------------------------------------------------------------")

// hoisting: 
a = 3 // a is global 
var a; // a is now local in its block. 

// prototype 
//ClassName.prototype.variableOrMethodName = ... // this way you are extending class methods and variables 
String.prototype.printName = function (age) {
 	console.log(this + age)
}
"Hadi".printName(31) // Hadi31

console.log("-------------------------------------------------------------------------")

class Human {
	constructor (name,age) {
		this.name = name; 
		this.age = age 
	}
	introduce () {
		console.log(this.name+this.age)
	}
	// this refers to the instance of the object of this class 
}
var hadi = new Human("HADI",31)
hadi.introduce();

console.log("-------------------------------------------------------------------------")

// array and objects are passed by refrence not value. 
var arr = [1,2,3,4]
var arrCopybyValue = arr.slice(0)

var obj = {"name":"ghasem"}
var objCopybyValue = Object.assign({},obj) // first argument is empty object. then assign "obj" values to the empty object and returns. copy by value. 

console.log("-------------------------------------------------------------------------")

/* not working
arr.push()
arr.concat()
arr.splice() // adds and removes from array 
object.assign({},{"name":"ghasem"})
setTimeOut(function(){},1000). // repeats once 
setInterval(function(){},1000) // repeats forever
str.split()
str.replace()
str.trim()
str.toLowerCase()
str.toUpperCase()
str.slice(index1,index2) // cut string 
 
 */



