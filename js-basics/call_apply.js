function Circle(R, C){ //OLD
    this.radius = R,
    this.color = C,
    this.draw = function(){ // or use prototype to remove from constructor 
        console.log('draw '+ this.radius);
    }
    //in inheritence we use call
}


class Cercle{
    constructor(R, C){ //NEW
        this.radius = R;
        this.color = C;
    }
    draw(){
        console.log('draw '+ this.radius);
    }
    //in inheritence we use super

}

let c1 = new Circle(11.2, 'Red');
let c2 = new Cercle(11.2, 'Red');
c1.draw();
c2.draw();

//Circle.call({},11.3,'red');
//Circle.apply({}, [11.4,'red']); 

//c2.draw();

/*

function notifyClient(message) {
    alert(message);
  }
  
  function sendMail(customer, total) {  
    notifyClient.call(this, `TODO: Send mail, (${String(customer.id)}, ${String(total)})`);
  }
  
  function getDeals() {  
      var product = arguments[0];
    var minPrice = arguments[1];
    
    product.price = Math.round(product.price * 0.9, 2);
    
    if(product.price < minPrice) {
        product.price = minPrice;
    }
  }
  
  class ShopCart{
    constructor() {
        this.items = [];
      this.customer = { id: 1 };
    }
  
    total() {
      var total = 0;
      var item;
  
      for(var i=0, c=this.items.length; i<c; i++){
        item = this.items[i];
        total += item.price * item.quantity; 
      }
  
      return total;
    }
  
    addItem(product) {
      this.getDealsByProduct(product);
      this.items.push(product);
      notifyClient.call(this, 'Item added ' + product.name);
    }
  
    getDealsByProduct(product) {
      getDeals.apply(this, [product, product.price * 0.6]);
    }
  
    placeOrder() {
      sendMail.apply(this, [this.customer, this.total()]);
    }
  };
  
  var shopCart = new ShopCart();
  
  shopCart.addItem({
    id: 1,
    name: 'Xbox Game',
    price: 179.00,
    quantity: 1
  });
  
  shopCart.placeOrder();
*/