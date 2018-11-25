var https = require('https');

function getMovieTitles(substr) {
    pageNum = 1;
    let url = 'https://jsonmock.hackerrank.com/api/movies/search/?Title=' + substr + "&page=" + pageNum;
    https.get(url, (res) => {
        res.setEncoding('utf8');
        res.on('data', function(body) {
            let dataRec = JSON.parse(body);
            let movies = dataRec.data;
            let totPages = dataRec.total_pages;
            let sortArray = [];
            for(let i = 0; i < movies.length; i++){
                console.log(movies[i].Title);
                sortArray.push(movies[i].Title);
            }
            /*movies.map((a) => {
              sortArray.push(a.Title)
            })*/
            for (let i = 2; i <= totPages; i++) {
                let newPage = i;
                let url1 = 'https://jsonmock.hackerrank.com/api/movies/search/?Title=' + substr + "&page=" + newPage;
                https.get(url1, (res) => {
                    res.setEncoding('utf8');
                    res.on('data', function(body) {
                        let newData = JSON.parse(body);
                        let newMovies = newData.data;
                        for (let i = 0; i < newMovies.length; i++) {
                            sortArray.push(newMovies[i].Title);
                        }
                        console.log(sortArray.sort());
                    })
                })
            }
        })
    })
}

//primary function 

getMovieTitles("Spiderman");

/*const obj = {
    prop: 'a',
    undefined: [{prop : 'b'}]
};
const logProp = function(obj){
    Console.log(obj.prop)
};

const a = obj;
[a].forEach(logProp);*/

/*let arr=["A","B","C","D","E","F"];
console.log(fib(12));

function dec_to_hex(n){
    let str = "";
    while(n != 0){
        rem = (n%16);
        if(rem >= 10) str+=arr[rem-10];
        else str += rem.toString();
        n = Math.floor(n/16);
    }
    console.log(str.split("").reverse("").join(""));
}   

function fib(n, mem=[]){
    if(mem[n]) return mem[n];
    if(n<=2) return 1;
    return mem[n] = fib(n-1,mem)+fib(n-2,mem);
}

fib(12);

//2D array
let arrs = [
    [1,2],[3,4]
];

function arrays(arrs){
    for(let i = 0; i <  arrs.length; i++){
        for(let j = 0; j <  arrs.length; j++)
            console.log(arrs[i][j]);
    }
}

let arrr=[-1,2,30,-3,12];

function shuffle(arrr){
    console.log(arrr);
    let j, temp;
    for(let i=0; i < arrr.length; i++){
        j = Math.floor(Math.random()*(arrr.length-i))+i;
        //console.log(j);
        let temp  = arrr[i];
        arrr[i] = arrr[j];
        arrr[j] = temp;
    }
    console.log(arrr);
}

let arr1=[1,2,3];
let arr2=[2,3,4];

function mergearr(arr1, arr2){
    arr3 = arr1.concat(arr2);
    return arr3;
}

Array.prototype.unique = function(){
    let hash = {};
    for(let i=0; i < this.length; i++){
       if( !hash[this[i]] )
           hash[this[i]] = 1;
    }
    let arrrr =[];
    for(let i in hash){
        console.log(i);
        arrrr.push(parseInt(i,10));
     }
    //let arr = (Object.keys(hash)).map(Number);
    return arrrr;
}

class Animal{
    constructor(id,name){
        this.id =id;
        this.name=name;
    }
    sound(){
        if(this.name=="dog")
            return "bark";
        else if(this.name == "duck")
            return "ddddaaa";
        else
            return "booooz";
    }
}

class Dog extends Animal{
    constructor(id, name, breed='pom'){
        super(id, name);
        this.breed = breed;
    }
    bark(){
        return "barkkkking";
    }
}

let animaaaaal = new Animal(123213123,"dog");
let puppy = new Dog(12,"nameeeee");
console.log(puppy.name);
console.log(puppy.sound());
console.log(puppy.bark());


console.log(mergearr(arr1, arr2));
console.log(mergearr(arr1, arr2).unique());

//shuffle(arrr)

//arrays(arrs);

//console.log(arrs[0][1]);
//OO

//if(arr.indexOf("A")>-1) console.log("yooo");







console.log(arr.sort(function (a,b) {
    return a-b;
}));

console.log(arr.sort( (a,b) => a-b ));
function sortCallback(a,b){
    return a-b;
}
console.log(arr.sort(sortCallback));



dec_to_hex(7562);

*/