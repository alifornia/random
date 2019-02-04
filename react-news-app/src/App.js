import React, { Component } from "react";
import { DragDropContext, Droppable, Draggable } from "react-beautiful-dnd";
import SearchBox from './components/searchBox';
import Pagination from './components/pagination';
import "./App.css";

//Ali: using dnd doc
// a little function to help us with reordering the result
const reorder = (list, startIndex, endIndex) => {
  const result = Array.from(list);
  const [removed] = result.splice(startIndex, 1);
  result.splice(endIndex, 0, removed);

  return result;
};

const grid = 8;

const getItemStyle = (isDragging, draggableStyle) => ({
  // some basic styles to make the items look a bit nicer
  userSelect: "none",
  padding: grid * 2,
  margin: `0 0 ${grid}px 0`,

  // change background colour if dragging
  background: isDragging ? "lightgreen" : "grey",

  // styles we need to apply on draggables
  ...draggableStyle
});

const getListStyle = isDraggingOver => ({
  background: isDraggingOver ? "lightblue" : "lightgrey",
  padding: grid,
  width: 250
});

class App extends Component {
  constructor(props) {
    super(props);

    this.state = {
      items: [],
      currentPage: 0,
      search: ""
    };
  }
  //this is expermental jsx which does binding by itself
  onDragEnd = result => {
    // dropped outside the list
    if (!result.destination) {
      return;
    }

    const items = reorder(
      this.state.items,
      result.source.index,
      result.destination.index
    );

    this.setState({
      items
    });
  };

  updatePage = event => {
    //console.log(event);
    this.setState({
      currentPage: +event.target.id
    });
  };

  //Ali: using https://newsapi.org/docs/client-libraries/node-js
  updateSearch = event => {
    const NewsAPI = require("newsapi");
    const newsapi = new NewsAPI("");     // Ali: add your API key


    newsapi.v2
      .topHeadlines({
        q: event.target.value,
        language: "en",
        country: "us"
      })
      .then(response => {
        this.setState({
          items: response.articles.map(function (d, i) {
            return {
              id: `${i}`,
              headline: d.title,
              url: d.url
            };
          })
        });
      });
    this.setState({
      search: event.target.value
    });
  };

  componentDidMount() {
    const NewsAPI = require("newsapi");
    const newsapi = new NewsAPI("");     // Ali: add your API key


    newsapi.v2
      .topHeadlines({
        q: "",
        language: "en",
        country: "us"
      })
      .then(response => {
        this.setState({
          items: response.articles.map(function (d, i) {
            return {
              id: `${i}`,
              headline: d.title,
              url: d.url
            };
          })
        });
      });
  }
  //Ali: calculates the number of pages for pagination
  // can be written cleaner
  getPageNumbers() {
    const itemsPerPage = 10;
    const currentPage = this.state.currentPage;
    const firstNewsIndex = itemsPerPage * currentPage;
    const lastNewsIndex = itemsPerPage * (currentPage + 1);
    const currentItems = this.state.items.slice(firstNewsIndex, lastNewsIndex);
    console.log(currentItems);

    const pageNumbers = [];
    for (let i = 0; i < Math.ceil(this.state.items.length / itemsPerPage); i++) {
      pageNumbers.push(i);
    }

    const renderPageNumbers = pageNumbers.map(number => {
      return (
        <li
          className="page-number"
          key={number}
          id={number}
          onClick={this.updatePage}
        >
          {number + 1}
        </li>
      );
    });
    return { currentItems, renderPageNumbers };
  }

  render() {
    let { currentItems, renderPageNumbers } = this.getPageNumbers();
    return (
      <div>
        <SearchBox onChange={this.updateSearch} value={this.state.search}></SearchBox>
        <Pagination pageNumbers={renderPageNumbers} ></Pagination>

        <DragDropContext onDragEnd={this.onDragEnd}>
          <Droppable droppableId="droppable">
            {(provided, snapshot) => (
              <div
                ref={provided.innerRef}
                style={getListStyle(snapshot.isDraggingOver)}
              >
                {currentItems.map((item, index) => (
                  <Draggable key={item.id} draggableId={item.id} index={index}>
                    {(provided, snapshot) => (
                      <div
                        ref={provided.innerRef}
                        {...provided.draggableProps}
                        {...provided.dragHandleProps}
                        style={getItemStyle(
                          snapshot.isDragging,
                          provided.draggableProps.style
                        )}
                      >
                        <a href={item.url} target="_blank">
                          {item.headline}
                        </a>
                      </div>
                    )}
                  </Draggable>
                ))}
                {provided.placeholder}
              </div>
            )}
          </Droppable>
        </DragDropContext>
      </div>
    );
  }
}

export default App;
