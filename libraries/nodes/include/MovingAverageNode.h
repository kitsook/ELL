////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     MovingAverageNode.h (nodes)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AccumulatorNode.h"
#include "BinaryOperationNode.h"
#include "ConstantNode.h"
#include "DelayNode.h"

// model
#include "Node.h"
#include "ModelTransformer.h"
#include "PortElements.h"
#include "InputPort.h"
#include "OutputPort.h"

// utilities
#include "TypeName.h"

// stl
#include <string>
#include <vector>

namespace nodes
{
    /// <summary> A node that takes a vector input and returns its mean over some window of time. </summary>
    template <typename ValueType>
    class MovingAverageNode : public model::Node
    {
    public:
        /// @name Input and Output Ports
        /// @{
        static constexpr const char* inputPortName = "input";
        static constexpr const char* outputPortName = "output";
        const model::OutputPort<ValueType>& output = _output;
        /// @}

        /// <summary> Default Constructor </summary>
        MovingAverageNode();

        /// <summary> Constructor </summary>
        /// <param name="input"> The signal to take the mean of </param>
        /// <param name="windowSize"> The number of samples of history to use in computing the mean </param>
        MovingAverageNode(const model::PortElements<ValueType>& input, size_t windowSize);

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return utilities::GetCompositeTypeName<ValueType>("MovingAverageNode"); }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        virtual std::string GetRuntimeTypeName() const override { return GetTypeName(); }

        /// <summary> Gets an ObjectDescription for the type </summary>
        ///
        /// <returns> An ObjectDescription for the type </returns>
        static utilities::ObjectDescription GetTypeDescription();

        /// <summary> Gets an ObjectDescription for the object </summary>
        ///
        /// <returns> An ObjectDescription for the object </returns>
        virtual utilities::ObjectDescription GetDescription() const override;

        /// <summary> Sets the internal state of the object according to the description passed in </summary>
        ///
        /// <param name="description"> The `ObjectDescription` to get state from </param>
        virtual void SetObjectState(const utilities::ObjectDescription& description, utilities::SerializationContext& context) override;

        /// <summary> Makes a copy of this node in the model being constructed by the transformer </summary>
        virtual void Copy(model::ModelTransformer& transformer) const override;

        /// <summary> Refines this node in the model being constructed by the transformer </summary>
        virtual bool Refine(model::ModelTransformer& transformer) const override;

    protected:
        virtual void Compute() const override;

    private:
        // Inputs
        model::InputPort<ValueType> _input;

        // Output
        model::OutputPort<ValueType> _output;

        // Buffer
        mutable std::vector<std::vector<ValueType>> _samples;
        mutable std::vector<ValueType> _runningSum;
        size_t _windowSize;
    };
}

#include "../tcc/MovingAverageNode.tcc"