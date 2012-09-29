/*	This file is part of YA3DE.

	YA3DE is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Foobar is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with YA3DE.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef _VERTEXDECLARATION_H_
#define _VERTEXDECLARATION_H_

#include <YA3DE/Helpers.h>
#include <YA3DE/OpenGL.h>
#include <memory>
#include <list>

namespace YA3DE
{
	namespace Graphics
	{
		enum VertexElementFormat
		{
			Vector2,
			Vector3,
			Vector4,
		};

		enum VertexElementUsage
		{
			Position,
			Normal,
			Color,
			TextureCoordinate,
		};

		struct VertexElement
		{
			VertexElement(VertexElementFormat type, VertexElementUsage kind, int unit = 0)
				: _Type(type), _Kind(kind), _Unit(unit)
			{
				
			}

			void Activate(int index, int offset, int stride)
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, ValueCount, GLType, GL_FALSE, stride, (void *)offset);
			}

			DEFPROP_SELF_RO(public, int, GLType)
			{
				switch (_Type)
				{
					case VertexElementFormat::Vector2:
					case VertexElementFormat::Vector3:
					case VertexElementFormat::Vector4:
						return GL_FLOAT;
				}

				return 0;
			}

			DEFPROP_SELF_RO(public, int, SizeInBytes)
			{
				switch (_Type)
				{
					case VertexElementFormat::Vector2:
						return 8;
					case VertexElementFormat::Vector3:
						return 12;
					case VertexElementFormat::Vector4:
						return 16;
				}

				return 0;
			}
			
			DEFPROP_SELF_RO(public, int, ValueCount)
			{
				switch (_Type)
				{
					case VertexElementFormat::Vector2:
						return 2;
					case VertexElementFormat::Vector3:
						return 3;
					case VertexElementFormat::Vector4:
						return 4;
				}

				return 0;
			}
			
			DEFPROP_RO(public, VertexElementFormat, Type);
			DEFPROP_RO(public, VertexElementUsage, Kind);
			DEFPROP_RO(public, int, Unit);
		};

		class VertexDeclaration
		{
		public:
			VertexDeclaration(VertexElement *elements, int size)
				: _Elements(elements, elements + size)
			{
			}

			void Activate()
			{
				int offset = 0;
				int stride = TotalSize;
				int index = 0;

				std::list<VertexElement>::iterator it;
				for (it = _Elements.begin(); it != _Elements.end(); it++)
				{
					it->Activate(index, offset, stride);
					offset += it->GetSizeInBytes();
					index++;
				}
			}
			
			DEFPROP_SELF_RO(public, int, TotalSize)
			{
				int size = 0;

				std::list<VertexElement>::iterator it;
				for (it = _Elements.begin(); it != _Elements.end(); it++)
					size += it->GetSizeInBytes();

				return size;
			}
			
			DEFPROP_RO_R(public, std::list<VertexElement>, Elements);
		};
	}
}

#endif
