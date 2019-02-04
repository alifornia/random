import React, { Component } from "react";

//just to show I know how to write my own react components :p
class Pagination extends Component {
    render() {
        return (
            <ul>{this.props.pageNumbers}</ul>
        );
    }
}

export default Pagination;
