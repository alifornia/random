//const
<<<<<<< HEAD
const name = 'Ali Abbasinasab';
=======
const name='Ali Abbasinasab';
>>>>>>> refs/remotes/origin/master

//variable
let greating = 'Yo ';
let age = 30;
let isApproved = true;
let nickname = undefined;
let race = null;
console.log(greating + name);

//object
let person = {
    name: 'Ali',
    age: 30
};
console.log(person);


person.name = 'Alex';
console.log(person.name);

//person[name] = 'Allie';
let property = 'name';
<<<<<<< HEAD
person[property] = 'Allie';
=======
person[property]= 'Allie'; 
>>>>>>> refs/remotes/origin/master
console.log(person.name);

//array
let colors = ['red', 'blue'];
colors[2] = 'green';
colors[3] = 367421;
console.log(colors);
console.log(colors.length);

//function
<<<<<<< HEAD
function greet(name = 'Alex') {
    console.log('Yo ' + name);
}

function square(number) {
    return number * number;
=======
function greet(name = 'Alex'){
    console.log('Yo ' + name);
}

function square(number){
    return number*number;
>>>>>>> refs/remotes/origin/master
}

greet();
greet('Ali');

let sqr = square(9);
console.log(square(99));

//template (web is not important for now -- node error)
/*
let template =  `<h2> Hey, ${name}!
Did you know the square of your age, ${age}, is ${square(`${age}`)}? </h2>`;
document.getElementById('templateid').innerHTML = template; 
*/

//OO
<<<<<<< HEAD
class User {
    constructor(username, email, password) {
=======
class User{
    constructor(username, email, password){
>>>>>>> refs/remotes/origin/master
        this.username = username;
        this.email = email;
        this.password = password;
    }
<<<<<<< HEAD
    regirster() {
        console.log(this.username + ' is registered');
    }
    static countUsers() {
=======
    regirster(){
        console.log(this.username + ' is registered');
    }
    static countUsers(){
>>>>>>> refs/remotes/origin/master
        console.log('There are 50 users');
    }
}

<<<<<<< HEAD
let bob = new User('bob', 'bob@eemail.com', 'notlikethisreallife');
bob.regirster();
User.countUsers();

class Member extends User {
    constructor(username, email, password, memberPackage) {
        super(username, email, password);
        this.memberPackage = memberPackage;
    }
    getPackage() {
        console.log(this.username + ' is subscribed to ' + this.memberPackage + ' package');
    }
}

let bobm = new Member('Bobm', 'bobm@gmail.com', 'notreal', 'vip');
=======
let bob =  new User('bob', 'bob@eemail.com', 'notlikethisreallife');
bob.regirster();
User.countUsers();

class Member extends User{
    constructor(username, email, password, memberPackage){
        super(username, email, password);
        this.memberPackage = memberPackage;
    }
    getPackage(){
        console.log(this.username + ' is subscribed to '+ this.memberPackage + ' package');
    }
}

let bobm = new Member('Bobm', 'bobm@gmail.com' , 'notreal', 'vip');
>>>>>>> refs/remotes/origin/master
bobm.regirster();
bobm.getPackage();

