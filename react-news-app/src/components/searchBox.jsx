import React, { Component } from "react";

//just to show I know how to write my own react components :p
class SearchBox extends Component {
    render() {
        return (
            <input
                type="text"
                onChange={this.props.onChange}
                value={this.props.value}
            />
        );
    }
}

export default SearchBox;
