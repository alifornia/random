
<<<<<<< HEAD
let name = "ali";

class Animal {
	constructor(name, type) {
		this.name = name;
		this.type = type;
	}
	break() {
		if (this.name == "doggy") return true;
	}
}

class Dog extends Animal {
	constructor(name, type, breed) {
		super(name, type);
		this.breed = breed;
	}
}

let puppy = new Dog("Zik", "Dog", "Pep");
console.log(puppy.type);

let a = 0.1;
let b = 0.2;
let c = 0.3;

if ((a + b).toPrecision(1) == c.toPrecision(1)) {
	console.log('yay');
}





// promise 
var promise = new Promise(function (resolve, reject) {
	resolve('returns this value when resolved.');
});
promise.then(function (value) {
	console.log(value);
});

var anotherPromise = new Promise(function (resolve, reject) {
	resolve("another resolved value... ");
});
// handling multiple promises 
Promise.all([promise, anotherPromise]).then(function (resultArr) {
	console.log(resultArr)// result is in order 
})
Promise.race([promise, anotherPromise]).then(function (firstResult) {
=======



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
>>>>>>> refs/remotes/origin/master
	console.log(firstResult)// result is in order 
})

console.log("-------------------------------------------------------------------------")

//clousure: 
function add(a) { // a =2
<<<<<<< HEAD
	return function (b) { // b = 3
		return a + b
	}
=======
   	return function (b) { // b = 3
    	return a+b
   }
>>>>>>> refs/remotes/origin/master
}

console.log(add(2)(3)) // 5

console.log("-------------------------------------------------------------------------")

// hoisting: 
<<<<<<< HEAD
aq = 3 // a is global 
var aq; // a is now local in its block. 
=======
a = 3 // a is global 
var a; // a is now local in its block. 
>>>>>>> refs/remotes/origin/master

// prototype 
//ClassName.prototype.variableOrMethodName = ... // this way you are extending class methods and variables 
String.prototype.printName = function (age) {
<<<<<<< HEAD
	console.log(this + age)
=======
 	console.log(this + age)
>>>>>>> refs/remotes/origin/master
}
"Hadi".printName(31) // Hadi31

console.log("-------------------------------------------------------------------------")

class Human {
<<<<<<< HEAD
	constructor(name, age) {
		this.name = name;
		this.age = age
	}
	introduce() {
		console.log(this.name + this.age)
	}
	// this refers to the instance of the object of this class 
}
var hadi = new Human("HADI", 31)
=======
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
>>>>>>> refs/remotes/origin/master
hadi.introduce();

console.log("-------------------------------------------------------------------------")

// array and objects are passed by refrence not value. 
<<<<<<< HEAD
var arr = [1, 2, 3, 4]
var arrCopybyValue = arr.slice(0)

var obj = { "name": "ghasem" }
var objCopybyValue = Object.assign({}, obj) // first argument is empty object. then assign "obj" values to the empty object and returns. copy by value. 
=======
var arr = [1,2,3,4]
var arrCopybyValue = arr.slice(0)

var obj = {"name":"ghasem"}
var objCopybyValue = Object.assign({},obj) // first argument is empty object. then assign "obj" values to the empty object and returns. copy by value. 
>>>>>>> refs/remotes/origin/master

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



