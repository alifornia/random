//const
const name='Ali Abbasinasab';

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
person[property]= 'Allie'; 
console.log(person.name);

//array
let colors = ['red', 'blue'];
colors[2] = 'green';
colors[3] = 367421;
console.log(colors);
console.log(colors.length);

//function
function greet(name = 'Alex'){
    console.log('Yo ' + name);
}

function square(number){
    return number*number;
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
class User{
    constructor(username, email, password){
        this.username = username;
        this.email = email;
        this.password = password;
    }
    regirster(){
        console.log(this.username + ' is registered');
    }
    static countUsers(){
        console.log('There are 50 users');
    }
}

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
bobm.regirster();
bobm.getPackage();

